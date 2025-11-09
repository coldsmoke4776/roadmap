#include "pool.h"
#include <stdint.h> // for uintptr_t

void pool_init(struct pool_t *p, void *buffer, size_t total_size){
    // Defensive programming check for NULL input
    if (p == NULL || buffer == NULL || total_size == 0) return;
    // Set the fields, as we're initializing the pool struct
    p->buffer = (uint8_t *)buffer; // need to cast to uint8_t because it's memory.
    p->total_bytes = total_size;
    p->offset = 0;
    p->highwater = 0;
}

void *pool_alloc(struct pool_t *p, size_t size, size_t align){
    // Defensive programming check for NULL input
    if (p == NULL || size == 0) return NULL;
    if (align == 0) align = sizeof(void *); // if the caller passes align == 0, we pick a sane alignment. Returned pointers will be safe.
    if ((align & (align - 1)) != 0) return NULL; // invalid alignment.
    uintptr_t cur = (uintptr_t)p->buffer + p->offset; // Current pointer is (casted to uintptr_t) the value of buffer + offset.
    /*
Imagine a ruler laid along memory with tick marks every align bytes (like fence posts every 8 bytes). 
You have a current pointer cur (somewhere between two posts). You want to snap cur forward to the next fence post 
(or stay on it if you’re already on one).
We do two simple moves to snap to a post:
Step forward a little (cur + (align - 1)) so you’re guaranteed past the post if you were partway through a block.
Chop off the remainder by clearing the low bits — that drops you down to the start of the post you landed in.
That’s exactly what this next line does 
*/
    uintptr_t aligned = (cur + (align - 1)) & ~(uintptr_t)(align - 1);
    size_t need = (size_t)(aligned - (uintptr_t)p->buffer) + size;
    if (need > p->total_bytes) return NULL; /* out of space */
    p->offset = need;
    if (p->offset > p->highwater) p->highwater = p->offset;
    return (void *)aligned;
}

void pool_reset(struct pool_t *p){
    if(!p) return;
    p->offset = 0;
} // fast reset to zero

size_t pool_mark(const struct pool_t *p){
    return p ? p->offset : 0; /* same as: return (p != NULL) ? p->offset : 0; */
} // intended to return current offset

void pool_restore(struct pool_t *p, size_t mark){
    if (!p) return;
    /* Only restore to a mark that is within the pool bounds. */
    if (mark <= p->total_bytes) p->offset = mark;
} // intended to rewind to mark

size_t pool_remaining(const struct pool_t *p) {
    if (!p) return 0;
    return (p->total_bytes > p->offset) ? (p->total_bytes - p->offset) : 0;
}
