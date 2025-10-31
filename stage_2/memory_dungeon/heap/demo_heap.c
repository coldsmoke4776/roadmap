#include <stdio.h>
#include "heap.h"

void run_heap_demo() {
    heap_init();

    int size;
    while (1) {
        printf("Enter the number of bytes you want to allocate: \n");
        if (scanf("%d", &size) != 1) {
            printf("Invalid input. Please enter a number. \n");
            break;
        };

        if (size == 0) {
            printf("Exiting Heap Hallway...\n");
            break;
        };

        void *ptr = heap_alloc(size);
        if (ptr == NULL) {
            printf("Allocation of %d bytes failed. \n", size);
        } else {
            printf("Allocation of %d bytes succesful at %p\n", size, ptr);
        };

        heap_dump();
    }
}

#if defined(STANDALONE)
int main() {
    run_heap_demo();
    return 0;
}
#endif
