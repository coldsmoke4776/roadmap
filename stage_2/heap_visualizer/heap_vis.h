#ifndef HEAP_VIS_H
#define HEAP_VIS_H

// std. includes for various pieces
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// define heap size, to utilize within various functions
#define HEAP_SIZE 64

typedef struct {
    uint8_t memory[HEAP_SIZE]; // The "heap" itself
    size_t offset; // current bump pointer / top of heap
} Heap;

void heap_init(Heap *h);
void *heap_alloc(Heap *h, size_t size);
void heap_print(const Heap *h);














#endif
//EOF