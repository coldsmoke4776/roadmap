#ifndef CLI_PARSER_H
#define CLI_PARSER_H

// Standard includes
#include <stddef.h>   // size_t
#include <stdlib.h>   // malloc, free
#include <stdio.h>    // fprintf, stderr

// Includes from previous stages - I have my own vector and string manipulation functions I wrote now.
#include "vector.h"   // for vector_t
#include "stringlib.h" // for matt_str* functions

/*
An enum (short for enumeration) defines a named set of possible values your program can emit or handle.
Think of it like a menu of tags your parser can attach to each token
*/

typedef enum {
    TOK_WORD, // plain argument
    TOK_FLAG_SHORT, // -a  (-abc would be broken into three of these)
    TOK_FLAG_LONG, // --verbose
    TOK_FLAG_LONG_KV, // --key=value
} tok_kind_t;

/*
Token shapes - where the token lives inside one shared buffer
*/
typedef struct {
    tok_kind_t kind;
    size_t start; // offset into out->buf
    size_t len; // bytes for this individual token

    // Only used specifically for the TOK_FLAG_LONG_KV type
    size_t key_off;
    size_t key_len;
    size_t val_off;
    size_t val_len;
} token_t;

/*
Parse result container - owns the decoded bytes and the list of tokens post-parse
*/
typedef struct {
    vector_t *tokens; //vector <tokens>, which we already wrote!
    char *buf; // buffer of contiguous bytes to hold tokens
    size_t cap; // capacity of buffer
    size_t bw; // buffer write - this is the cursor that goes from 0..cap

    int error; // error code = 0, is ok.  error code !=0, is error that we'll define later
    size_t err_pos; // index into input where error is detected, helps with debugging.
} parse_result_t;


// function prototypes
int cli_parse(const char *input, parse_result_t *out);
void cli_parse_free(parse_result_t *out);
/* static int buf_putc(parse_result_t *out, char c);
static int buf_reserve(parse_result_t *out, size_t extra);
static int read_quoted_double(const char **p, parse_result_t *out);
static int read_quoted_single(const char **p, parse_result_t *out);
static int read_word(const char **p, parse_result_t *out); */

#endif
