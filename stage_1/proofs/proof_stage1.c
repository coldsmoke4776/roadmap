#include <stdio.h>
#include "vector.h"
#include "linked_list.h"
#include "stringlib.h"
#include "cli_parser.h"

int main(void){
    printf("=== Stage 1 Proof Program - Utilizing everything I built to see if it works ===");
    printf("\n");
    // Stringlib demo
    char dest[64];
    matt_strcpy(dest, "Hello");
    matt_strcat(dest, " ,World!");
    printf("[Stringlib]: %s (len=%zu)\n", dest, matt_strlen(dest));
    printf("\n");

    // Vector demo
    vector_t *vec = vector_init(sizeof(int));
    for(int i = 0; i <5; i++){
        vector_push_back(vec, &i);
    }
    printf("Vector contents: ");
    for(size_t i = 0; i < vec->length; i++){
        int value;
        vector_get(vec, i, &value);
        printf("%d ", value);
    }
    printf("\n");

    // Linked List demo
    list_t *list = list_init(sizeof(int));
    for(int i = 10; i < 15; i++) list_push_back(list, &i);
    for (size_t i = 0; i < list->length; i++) {
        int value;
        list_get(list, i, &value);
        printf("%d ", value);
    }
    printf("\n");

    // CLI Parser demo
    const char *input = "ping -c  5 8.8.8.8";
    parse_result_t parsed = {0};
    cli_parse(input, &parsed);
    printf("[CLI Parser] tokens:\n");
    for (size_t i = 0; i < parsed.tokens->length; i++){
        token_t tok;
        vector_get(parsed.tokens, i, &tok);
        printf("  [%zu] '%.*s'\n", i, (int)tok.len, parsed.buf + tok.start);
    }
    // --- Cleanup ---
    vector_free(vec);
    list_free(list);
    cli_parse_free(&parsed);

    printf("\nAll systems nominal. Stage 1 complete. ✅\n");
    return 0;
}
