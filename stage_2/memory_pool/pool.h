#ifndef POOL_H
#define POOL_H

/*What the bump arena is going to be:

A tiny, resettable allocator that hands out aligned chunks from a single pre-allocated buffer by bumping an offset; 
no per-object frees — only reset/rewind/checkpoint semantics.*/

#include <stddef.h> // For uint8_t, uintptr_t if needed.
#include <stdio.h> // For size_t 

struct pool_t {
    uint8_t *buffer; // base pointer
    size_t total_bytes; // size of buffer
    size_t offset; // current bump offset (0...total bytes)
    size_t highwater; // optional, max offset observed (for stats/analytics)
};

// Compatibility shim for C++ so it doesn't mangle the function names if we include this in C++ code (learning soon!)
#ifdef __cplusplus
extern "C"{
#endif

void pool_init(struct pool_t *p, void *buffer, size_t total_size);
void *pool_alloc(struct pool_t *p, size_t size, size_t align); // align is a power of 2
void pool_reset(struct pool_t *p); // fast reset to zero
size_t pool_remaining(const struct pool_t *p); // diagnostic helper
size_t pool_mark(const struct pool_t *p); // intended to return current offset
void pool_restore(struct pool_t *p, size_t mark); // intended to rewind to mark

#ifdef __cplusplus
}
#endif














#endif
