#include "allocator.h"
#include <stdio.h>
#include <stdint.h>
#include "allocator.h"

int main(void) {
    struct allocator_t a;
    uint8_t buf[1024];

    allocator_init(&a, buf, sizeof(buf), 32);
    printf("init -> total_blocks=%zu free_count=%zu head=%p\n", a.total_blocks, a.free_count, a.free_list);

    void *p = allocator_alloc(&a);
    if (!p) { printf("alloc failed\n"); return 1; }
    printf("after alloc -> p=%p free_count=%zu head=%p\n", p, a.free_count, a.free_list);

    allocator_free(&a, p);
    printf("after free -> free_count=%zu head=%p\n", a.free_count, a.free_list);

    size_t drained = 0;
    while (allocator_alloc(&a)) ++drained;
    printf("drained %zu blocks, free_count=%zu\n", drained, a.free_count);

    return 0;
}

