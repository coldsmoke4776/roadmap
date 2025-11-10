#include "heap_vis.h"
#include <string.h> // for memset

// initialize heap, zero offset;
void heap_init(Heap *h){
    memset(h->memory, 0, HEAP_SIZE);
    h->offset = 0;
}

// allocate memory from simulated heap;
void *heap_alloc(Heap *h, size_t size){
    // Defensive programming check for null h and size input
    if (!h || size == 0) return NULL;
    // Is there enough space left within the heap to allocate? Let's check!
    if (h->offset + size > HEAP_SIZE){
        printf("!!! HEAP OVERFLOW, MY AMIGO !!! Requested %zu bytes, only %zu left!\n", size, HEAP_SIZE - h->offset);
        return NULL;
    }
    // Let's record our starting point for allocation
    void *ptr = &h->memory[h->offset]; // you need to use arrow notation within the index-type square brackets too, so it knows to reference the initialized 0 value of offset at the start.
    // Mark bytes as used (visual step) using a # symbol
    for (size_t i = 0; i < size; i++){
        h->memory[h->offset + i] = '#';
    }
    // Bump offset
    h->offset += size;
    // Return pointer
    return ptr;
}


// visualize heap state
void heap_print(const Heap *h) {
    // Defensive check for null  h input
    if (!h) return;
    printf("[");
    for(size_t i=0; i < HEAP_SIZE; i++){
        putchar(h->memory[i] ? '#' : '-');
    }
    printf("] %zu / %d bytes used\n", h->offset, HEAP_SIZE);
}

// simple demo sequence
int main(void) {
    Heap h;
    heap_init(&h);

    // call heap_alloc and heap_print in steps here
    heap_alloc(&h, 16);
    heap_print(&h);
    puts("--------------------------------------------");
    heap_alloc(&h, 24);
    heap_print(&h);
    puts("--------------------------------------------");
    heap_alloc(&h, 16);
    heap_print(&h);
    puts("--------------------------------------------");
    heap_alloc(&h, 16);
    heap_print(&h);
    puts("--------------------------------------------");

    return 0;
}