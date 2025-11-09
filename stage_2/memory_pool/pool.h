#ifndef POOL_H
#define POOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>   /* size_t */
#include <stdint.h>   /* uint8_t, uintptr_t */
#include <stdalign.h> /* optional: alignof(max_align_t) if you use it */

struct pool_t {
    uint8_t *buffer;    /* base pointer */
    size_t total_bytes; /* size of buffer */
    size_t offset;      /* current bump offset (0..total_bytes) */
    size_t highwater;   /* optional peak usage */
};

/* API */
void pool_init(struct pool_t *p, void *buffer, size_t total_size);
void *pool_alloc(struct pool_t *p, size_t size, size_t align);
void pool_reset(struct pool_t *p);
size_t pool_remaining(const struct pool_t *p);
size_t pool_mark(const struct pool_t *p);
void pool_restore(struct pool_t *p, size_t mark);

#ifdef __cplusplus
}
#endif

#endif /* POOL_H */
