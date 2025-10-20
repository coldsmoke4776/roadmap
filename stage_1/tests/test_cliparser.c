#include "cli_parser.h"
#include <stdio.h>

static void print_token(const parse_result_t *r, const token_t *t){
    printf("TOK(%d): '%.*s'\n", (int)t->kind, (int)t->len, r->buf + t->start);
    return;
}

int main(void){
    const char *input = "ping -c 8.8.8.8"; // Example input to trigger the parser.
    parse_result_t res = {0};

    int rc = cli_parse(input, &res);
    if (rc != 0){
        fprintf(stderr, "parse error %d at pos %zu\n", res.error, res.err_pos);
        cli_parse_free(&res);
        return 1;
    }

    for (size_t i =0; i < res.tokens->length; i++){
        token_t t;
        vector_get(res.tokens, i, &t);
        print_token(&res, &t);
    }
    cli_parse_free(&res);
    puts("OK");
    return 0;
}
