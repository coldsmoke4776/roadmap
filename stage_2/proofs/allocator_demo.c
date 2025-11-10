#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// include custom allocator
#include "../memory_pool/pool.h"

#define N_ALLOCS 16000
#define BLOCK_SIZE 64

// create global pool for demo purposes
static struct pool_t demo_pool;
static uint8_t pool_buffer[1024 * 1024]; // 1 MB buffer

//thin wrapper functions so custom pool actually plugs into the benchmarker
void *pool_alloc_adapter(size_t size) {
    return pool_alloc(&demo_pool, size, 0); // 0 = default alignment
}

void pool_free_adapter(void *ptr) {
    (void)ptr; // no-op since bump allocator can’t free individual blocks
}

/*Both the number being multiplied by and divided by here are what is 
required to convert seconds AND nanoseconds to milliseconds*/
double elapsed_ms(struct timespec start, struct timespec end){
    return (end.tv_sec - start.tv_sec) * 1000 +
    (end.tv_nsec - start.tv_nsec) / 1e6;
}

// reusable benchmark harness to allow for measuring of custom pool against anything.
void run_benchmark(const char *name, void *(*alloc_func)(size_t), void(*free_func)(void *)){
    //use timespec struct to start building the timing harness (the "stopwatch") for the benchmarker
    struct timespec start, end;
    // stopwatch starts
    clock_gettime(CLOCK_MONOTONIC, &start);
    // allocation goes here
    for (size_t i=0; i < N_ALLOCS; i++){
        // Cast the generic void * pointer you got from your allocator to a pointer to volatile char
        void *ptr = alloc_func(BLOCK_SIZE);
        ((volatile char *)ptr)[0] = 42;  // write to allocated memory
        free_func(ptr);
    }
    // stopwatch stops
    clock_gettime(CLOCK_MONOTONIC, &end);
    // note down the time and print it out in milliseconds - x1000 for secs>ms, divide by 1e6 for nanosecs>ms
    double ms = (end.tv_sec - start.tv_sec) * 1000 +
    (end.tv_nsec - start.tv_nsec) / 1e6;
    printf("%s: %.3f ms \n", name, ms);
}


// Main entry point into program.
int main(void ){
    pool_init(&demo_pool, pool_buffer, sizeof(pool_buffer));
    run_benchmark("malloc", malloc, free);
    run_benchmark("pool_alloc/free", pool_alloc_adapter, pool_free_adapter);

    return 0;
}

// EOF