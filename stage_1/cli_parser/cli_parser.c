#include "cli_parser.h"
#include <stdint.h>   // for SIZE_MAX


// internal helper - reserves capacity for the buffer for tokens
// Ensure out->buf has room for at least `extra` more bytes beyond out->bw.
// Grow with capacity doubling. Return 0 on success, nonzero on alloc failure
static int buf_reserve(parse_result_t *out, size_t extra){
    // if extra == 0, return 0 (nothing to do)
    if (extra == 0){
        return 0; // nothing to do
    }
    // If out->cap - out->bw >= extra, return 0 (already enough room).
    if (out->cap - out->bw >= extra){
        return 0; // already enough room
    }
    // We need to compute what our need for buffer capacity is somehow
    // need is basically "how many bytes we'll have written AFTER adding extra"
    size_t need = out->bw + extra;
    // newcap is a temp variable to hold the proposed new size to make the buffer so it fits everything!
    size_t newcap = (out->cap ? out->cap : 256); // value of newcap is either the current value of out_cap or a baseline of 256
    // if newcap is ever less than the need, we double it
    while (newcap < need){
        // avoid overflow on doubling
        if (newcap > SIZE_MAX / 2){
            newcap = need; // “just make it big enough once, don't double anymore”
            break;
        }
        newcap *= 2;
    }

    void *p = realloc(out->buf, newcap); 
    if (!p) return 1; // OOM, bail out
    out->buf = (char *)p;
    out->cap = newcap;
    return 0;
}

// Internal helper - append one byte to the buffer, extend if needed.
// Returns 0 on success, non-zero on OOM error
static int buf_putc(parse_result_t *out, char c){
    // Ensure capacity for one more byte
    if (buf_reserve(out, 1) != 0) return 1;
    // write the current byte at the current write cursor (bw)
    out->buf[out->bw] = c;
    // advance the cursor a step
    out->bw++;
    // return 0 for success
    return 0;
}

// Internal helper - read one "word" token from *p and copy it into out->buf
// Stops on space, tab or '\0'. Handles \ escapes outside quotes.
// Returns 0 on success, non-zero on OOM error.
static int read_word(const char **p, parse_result_t *out){
    /* read_word takes a pointer to a pointer, so it can move through the string, and also
    a pointer to your parse state (the parse_result_t struct we've been working with) */
    // First, we mark the starting position in the output buffer
    size_t start = out->bw;
    // Iterate over **p until we hit the delimiter or \0
    // This is the canonical C "infinite loop" - loop forever till I break out manually, basically.
    for (;;) {
        // current input character, as **p is a pointer to pointer to char
        char c = **p;
        // We can use the if statement to go through because c is a char, not a pointer
        if (c == '\0' || c == '\t' || c == ' '){
            break; // stop on NULL or whitespaces
        }
        // Handling backslash escapes - Check if character is equal to "\\"
        if (c == '\\'){
            char next = *(*p + 1); // Peek at the next character, we want to point at *p + 1.
            if (next == '\0'){
                break; // stop
            }
            (*p)++; // Advance pointer once to skip backslash
            // Write next to the buffer using buf_putc
            if (buf_putc(out, next) != 0){
                return 1; //OOM error
            }
            (*p)++; // Advance pointer again to advance past escaped character
            continue; // Skip the rest of the loop
        }
        // Now we need to write this byte to out->buf, so it gets stored somewhere.
        // This essentially checks whether buf_putc, the function we wrote to write one byte to the buffer worked or not
        if(buf_putc(out, c) != 0) {
            return 1; // OOM error
        }
        // Advance the caller's cursor, advancing **p would advance the CHAR not the pointer.
        (*p)++;
    }
    // Create a token_t entry for this word, because remember, we advance the cursor through the loop so it's moved!
    size_t len = out->bw - start;
    // the token_t tok = {0} is idiomatic C (consensus best practice) for "zero-initalize everything in this struct"
    token_t tok = {0};
    tok.kind = TOK_WORD;
    tok.start = start;
    tok.len = len;
    // Push that token into out->tokens
    vector_push_back(out->tokens, &tok);
    return 0;
}

// Internal helper - read a single quoted string - **p is at the opening '\''
// Copies bytes literally until the closing '\''
// Returns 0 on success, non-zero on OOM error
static int read_quoted_single(const char **p, parse_result_t *out){
    // First, we mark the starting position in the output buffer
    size_t start = out->bw;
    // Consume opening quote
    (*p)++;
    // Loop until we see closing quote or '\0'
    for (;;) {
        // current input character, as **p is a pointer to pointer to char
        char c = **p;
        // a) EOF before close -> error
        if (c == '\0') return 2; // different error code, for different error
        // b) closing quote -> consume it and break
        if (c == '\'') {
            (*p)++;
            break;
        }
        // c) normal byte: write & advance
         // Now we need to write this byte to out->buf, so it gets stored somewhere.
        // This essentially checks whether buf_putc, the function we wrote to write one byte to the buffer worked or not
        if(buf_putc(out, c) != 0) {
            return 1; // OOM error
        }
        // Advance the caller's cursor, advancing **p would advance the CHAR not the pointer.
        (*p)++;
    }
    // Create a token_t entry for this word, because remember, we advance the cursor through the loop so it's moved!
    size_t len = out->bw - start;
    // the token_t tok = {0} is idiomatic C (consensus best practice) for "zero-initalize everything in this struct"
    token_t tok = {0};
    tok.kind = TOK_WORD;
    tok.start = start;
    tok.len = len;
    // Push that token into out->tokens
    vector_push_back(out->tokens, &tok);
    return 0;
}

// Internal helper - read a double-quoted string - **p is at the opening '"'
// Returns 0 on success, non-zero on OOM error
static int read_quoted_double(const char **p, parse_result_t *out){
    // First, we mark the starting position in the output buffer
    size_t start = out->bw;
    // Consume opening quote
    (*p)++;
    // Loop until we see closing quote or '\0'
    for(;;){
        // current input character, as **p is a pointer to pointer to char
        char c = **p;
        // a) EOF before close -> error
        if (c == '\0') return 2; // different error code, for different error
        // b) if c = '"', consume it and break
        if (c == '"') {
            (*p)++;
            break;
        }
        // c) Handling backslash escapes - Check if character is equal to "\\"
        if (c == '\\'){
            char next = *(*p + 1); // Peek at the next character, we want to point at *p + 1.
            if (next == '\0'){
                return 2;
            }
            // translate a few escapes, else take literally
            char outc;
            switch (next) {
                case '\\': outc = '\\'; break;
                case '"': outc = '"'; break;
                case 'n': outc = '\n'; break;
                case 't': outc = '\t'; break;
                default: outc = next; break;
            }
            // Consume the backslash
            (*p)++;
            // Write next to the buffer using buf_putc
            if (buf_putc(out, outc) != 0){
                return 1; //OOM error
            }
            (*p)++; // Advance pointer again to advance past escaped character
            continue; // Skip the rest of the loop
        }
        // Write next to the buffer using buf_putc
        if (buf_putc(out, c) != 0){
            return 1; //OOM error
        }
        (*p)++;
    }
    // Create a token_t entry for this word, because remember, we advance the cursor through the loop so it's moved!
    size_t len = out->bw - start;
    // the token_t tok = {0} is idiomatic C (consensus best practice) for "zero-initalize everything in this struct"
    token_t tok = {0};
    tok.kind = TOK_WORD;
    tok.start = start;
    tok.len = len;
    // Push that token into out->tokens
    vector_push_back(out->tokens, &tok);
    return 0;
}

// Driver loop v1
int cli_parse(const char *input, parse_result_t *out){
    // Defensive programming check for no input or output, we want both!
    if (!input || !out){
        return -1; // error due to non-zero
    }
    // init result
    *out = (parse_result_t){0}; // zero-initialize the parse_result_t struct
    // using the vector_init function we wrote in vector.c
    out->tokens = vector_init(sizeof(token_t));

    const char *p = input;

    for (;;) {
        // skip spaces + tabs
        while (*p == ' ' || *p == '\t') p++;
        // end of input?
        if (*p == '\0') break;
        int rc = 0;
        // dispatch - quotes vs word
        if (*p == '"'){
            rc = read_quoted_double(&p, out);
        } else if (*p == '\''){
            rc = read_quoted_single(&p, out);
        } else {
            rc = read_word(&p, out);
        }

        if (rc != 0){
            out-> error = rc;
            out-> err_pos = (size_t)(p - input);
            break;
        }
    }
    return out->error; // 0 on success
}

void cli_parse_free(parse_result_t *out) {
    if (!out) return;
    free(out->buf);
    vector_free(out->tokens);
    *out = (parse_result_t){0};
}
