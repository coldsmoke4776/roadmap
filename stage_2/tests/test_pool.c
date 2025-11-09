// tests/test_pool_simple.c
// I used ChatGPT to write an extremely simple test harness just to test these basic functions, I'll come back and look at this again one day and add to it
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include "pool.h"

int main(void) {
    struct pool_t pool;
    enum { BUF_SZ = 1024 };
    uint8_t buf[BUF_SZ];

    /* init */
    pool_init(&pool, buf, sizeof(buf));

    /* simple alloc + alignment check (default align) */
    void *a = pool_alloc(&pool, 16, 0);
    if (!a) { fprintf(stderr, "alloc a failed\n"); return 1; }
    uintptr_t pa = (uintptr_t)a;
    if ((pa % (uintptr_t)sizeof(void *)) != 0) {
        fprintf(stderr, "alignment failure for a: %p\n", a);
        return 2;
    }

    /* mark / alloc / restore check */
    size_t before_remaining = pool_remaining(&pool);
    size_t mark = pool_mark(&pool);

    void *b = pool_alloc(&pool, 32, 8); /* 8-byte aligned */
    if (!b) { fprintf(stderr, "alloc b failed\n"); return 3; }
    if (((uintptr_t)b % 8) != 0) {
        fprintf(stderr, "alignment failure for b: %p\n", b);
        return 4;
    }

    pool_restore(&pool, mark);
    size_t after_restore = pool_remaining(&pool);
    if (before_remaining != after_restore) {
        fprintf(stderr, "restore failed: before=%zu after=%zu\n", before_remaining, after_restore);
        return 5;
    }

    /* reset check */
    pool_reset(&pool);
    size_t after_reset = pool_remaining(&pool);
    if (after_reset != sizeof(buf)) {
        fprintf(stderr, "reset failed: remaining=%zu expected=%zu\n", after_reset, sizeof(buf));
        return 6;
    }

    printf("SIMPLE POOL TEST: PASS\n");
    return 0;
}

