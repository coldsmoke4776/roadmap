#include "heap.h"   // Pulls in our header (function prototypes + <stddef.h>)
#include <stdio.h>  // Standard I/O (printf, putchar, etc.)

/* We're creating some "fake memory" to visualize how it works in real life.
   This is our simulated heap: a long hallway of 1024 rooms (bytes). */

#define HEAP_SIZE 1024
static unsigned char heap[HEAP_SIZE]; 
// static = private to this file (no other .c can see our hallway)
// Char is 8 bits/1 byte and is the smallest addressable size of memory we can access.
// heap is an array of size HEAP_SIZE.

// We mark heap and bump_pointer as static so they’re private to this file — nobody outside heap.c can touch our hallway internals

/* How do we know where the next free room is?
   For this first quest, we’ll use a simple counter called a bump pointer.
   When someone asks for N rooms, we give them the address of heap[bump_pointer]
   and then BUMP it forward by N. */

   /*You might think you could just count allocations in a simple linear fashion, 
   and that’s exactly what we’ll do for now with a bump pointer. 
   Later, when we add free(), rooms up and down the hallway can be RECLAIMED, 
   so we’ll need more sophisticated bookkeeping later on down the line.*/

static size_t bump_pointer = 0; 
// starts at 0 (the first room). This is an OFFSET into our hallway - how far we've walked into it.

/* The purpose of this function is to initialize the heap: reset the bump pointer back to the start. */
void heap_init() {
    bump_pointer = 0;
}

/*The purpose of this function is the logic that lets the "client" request a specific number (size) of rooms.
We need to do two things - check whether we have (size) rooms left at all, and then also point out where the first free room is. */
void *heap_alloc(size_t size) {
    if (bump_pointer + size > HEAP_SIZE) {
        fprintf(stderr, "Error: Out of memory \n");
        return NULL; // Returns NULL if we don't have enough rooms.
    }

    // Now, we need to save the address of the first free room (which will currently be 0) so we can actually USE it for stuff.
    void *ptr = &heap[bump_pointer];

    // Then, we add (size) to our bump pointer, so we can tell where the next free room in the hallway is.
    bump_pointer += size;

    // What we actually wanted out of all of this is that address of the next free room, so we need to return its location:
    return ptr;
}

// The purpose of this function is to provide a visual of how many rooms are taken up in the hallway at any given time.
void heap_dump() {
    double percent = (100 * bump_pointer) / HEAP_SIZE;
    printf("Heap usage: %zu / %d bytes (%.1f%%)\n", bump_pointer, HEAP_SIZE, percent); // Prints current heap usage.
    /* %zu tells the program to print bump_pointer as an UNSIGNED decimal, whereas %d tells the program to print HEAP_SIZE as a SIGNED decimal*/

    // We need to walk through every room in the hallway:
    for (size_t i=0; i<HEAP_SIZE; i++){
        if (i<bump_pointer) {
            putchar('#'); // allocated room
        } else {
            putchar('.'); // free room
        }

        // every 64 rooms, print a newline
        if (i % 64 == 63) {
            putchar('\n');
        }
    }
    putchar('\n'); // end the line.
} 
