#include "allocator.h"
#include <assert.h>
#include <stdio.h>
#include <string.h> // for memcpy

void allocator_init(struct allocator_t *allocator, void *buffer, size_t total_size, size_t block_size){
    // Defensive programming check for null allocator input
    if (allocator == NULL){
        fprintf(stderr, "Error - allocator_init: allocator == NULL\n");
        return;
    }
    // Defensive programming check for null buffer input
    if (buffer == NULL){
        fprintf(stderr, "Error - allocator_init: buffer == NULL\n");
        return;
    }
    // Defensive programming check for block_size == 0 error, as size_t is unsigned
    if (block_size == 0){
        fprintf(stderr, "Error - allocator_init: block_size must be > 0\n");
        return;
    }
    // Defensive programming check to ensure the block_size is enough to hold a pointer
    if (block_size < sizeof(void *)){
        fprintf(stderr, "Error - allocator_init: block_size (%zu) must be >= sizeof(void*) (%zu)\n", block_size, sizeof(void *));
        return;
    }
    // Defensive programming check to ensure that total_size is a multiple of block_size, or the allocator won't divide the space up evenly.
    if(total_size % block_size != 0){
        fprintf(stderr, "allocator_init: total_size (%zu) must be a multiple of block_size (%zu)\n", total_size, block_size);
        return;
    }
    // Assignment of allocator fields
    allocator->buffer = (uint8_t *)buffer;
    allocator->block_size = block_size;
    allocator->total_blocks = total_size / block_size;
    allocator->free_count = allocator->total_blocks;
    allocator->free_list = NULL; // We will wire this soon

    /* Now, we wire the free-list: each block stores a pointer to the next block in its first sizeof(void*) bytes */
    for (size_t i =0; i < allocator->total_blocks; ++i){
        uint8_t *block = allocator->buffer + i * allocator->block_size;
        void *next = (i + 1 < allocator->total_blocks) ? (void *)(allocator->buffer + (i + 1) * allocator->block_size) : NULL;
        *(void **)block = next;
    }

    allocator->free_list = (void *)allocator->buffer;
}

void *allocator_alloc(struct allocator_t *allocator){
    // Defensive programming check for NULL allocator - cheap and good hygeine
    if (allocator == NULL) return NULL;
    // Defensive programming check for out of memory error - if free_list is NULL, we've reached the end of the buffer.
    if (allocator->free_list == NULL) return NULL; 
    // capture the first block/head of the linked list - we are storing the pointer we'll return to the caller
    void *block = allocator->free_list;
    // Now, we need to advance the list safely - we're going to use memcpy
    void *next;
    memcpy(&next, allocator->free_list, sizeof(next));
    allocator->free_list = next;
    // Book-keeping - one less free block
    allocator->free_count--;
    // return block pointer - caller now owns the block - do not call free on anything but block-aligned pointers that come from THIS allocator
    return block;
}

void allocator_free(struct allocator_t *allocator, void *ptr){
    // Defensive check against NULL input
    if (allocator == NULL || ptr == NULL) return;
    // Pointer math
    uint8_t *p = (uint8_t *)ptr;
    size_t offset = (size_t)(p - allocator->buffer);
    size_t total_bytes = allocator->total_blocks * allocator->block_size;
    // Bounds check
    if (offset >= total_bytes){
        fprintf(stderr, "allocator_free: ptr out of range\n");
        return;
    }
    // Alignment check - ptr needs to be at a block boundary to avoid UB
    if (offset % allocator->block_size != 0){
        fprintf(stderr, "allocator_free: ptr not block-aligned\n"); 
        return;
    }
    // We now need block's next pointer - its a linked list
    void *next = allocator->free_list;
    memcpy(ptr, &next, sizeof(next)); /* store old head into this block's first bytes */
    // Push block onto head, update count
    allocator->free_list = ptr;
    allocator->free_count++;
}
