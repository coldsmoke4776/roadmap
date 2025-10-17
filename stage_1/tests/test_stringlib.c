// This is the test harness for the matt_stringlib library, we need to include the most basic headers necessary, plus stringlib.h
#include <stdio.h> // for printing results
#include <stdlib.h> // for return codes
#include <stdint.h> // for fixed-width types
#include "../stringlib/stringlib.h" // for our function protofypes

static int tests_run = 0;
static int tests_failed = 0;

static void expect_true(const char *name, int condition){
    tests_run++;
    if (!condition){
        tests_failed++;
        printf("[FAIL] %s\n", name);
    } else {
        printf("[OK] %s\n", name);
    }
}

static void expect_str_eq(const char *name, const char *got, const char *want){
    tests_run++;
    if (matt_strcmp(got, want) != 0){
        tests_failed++;
        printf("[FAIL] %s\n       got: \"%s\"\n      want: \"%s\"\n", name, got, want);
    } else {
        printf("[OK] %s\n", name);
    }
}

static void dump_bytes(const char *label, const unsigned char *buf, size_t n) {
    printf("%s:", label);
    for (size_t i = 0; i < n; ++i) printf(" %02X", buf[i]);
    printf("\n");
}

int main(void) {
    printf("==== stringlib tests ==== \n\n");

    // strcpy basic test
    {
        char dest[16];
        char *ret = matt_strcpy(dest, "hello");

        expect_true("strcpy returns dest", ret == dest);
        expect_str_eq("strcpy basic copy", dest, "hello");
    }

    // strcpy empty src
    {
        char dest[4] = {'X','X','X','X'};
        dump_bytes("before", (unsigned char*)dest, sizeof(dest));
        matt_strcpy(dest, "");
        dump_bytes("after ", (unsigned char*)dest, sizeof(dest));
    }

    // strcpy exact fit
    {
        char dest[4] = {0}; // room for "abc" but also "\0"
        matt_strcpy(dest, "abc");
        expect_str_eq("strcpy exact fit content", dest, "abc");
        expect_true("strcpy exact fit terminator", dest[3] == '\0');
    }

    // strcat basic
    {
        char dest[32] = "Hello";
        char *ret = matt_strcat(dest, " World");
        expect_true("strcat returns dest", ret == dest);
        expect_str_eq("strcat basic append", dest, "Hello World");
    }

    // strcat empty src (should not change dest)
    {
        char dest[8] = "A";
        matt_strcat(dest, "");
        expect_str_eq("strcat empry src keeps dest", dest, "A");
    }

    // strcat empty dest (dest starts empty)
    {
        char dest[8] = "";
        matt_strcat(dest, "abc");
        expect_str_eq("strcat empty dest become src", dest, "abc");
    }

    // strcat multi-append (sequential appends)
    {
        char dest[32] = "";
        matt_strcat(dest, "Hi");
        matt_strcat(dest, ", ");
        matt_strcat(dest, "Matt!");
        expect_str_eq("strcat multi-append", dest, "Hi, Matt!");
    }



    printf("\nTests run: %d\nTests failed: %d\n", tests_run, tests_failed);
    printf("Result: %s\n", tests_failed ? "FAIL ❌" : "PASS ✅");
    return tests_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
