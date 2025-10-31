#ifndef ALLOCATOR_H
#define ALLOCATOR_H

// Includes for types
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct allocator_t {
    uint8_t *buffer; // Byte-level pointer for indexing and arithmetic.
    size_t block_size; // Unsigned, machine-word sized count of bytes, per block
    size_t total_blocks; // Count of total blocks, same sketch as above.
    void *free_list; // Generic pointer to the head of the singly linked list
    size_t free_count; // Useful counter for diagnostics.
};

void allocator_init(struct allocator_t *allocator, void *buffer, size_t total_size, size_t block_size); // We don't need this to return anything, the information isn't going anywhere, it just needs to initialize?
void *allocator_alloc(struct allocator_t *allocator); // We want the pointer to the actual allocated memory block, so this needs to be a void *
void allocator_free(struct allocator_t *allocator, void *ptr); // Reverse of allocator_alloc logic
int allocator_stats(struct allocator_t *allocator); // We will choose later what type this will be, will leave as int for now.






#endif
