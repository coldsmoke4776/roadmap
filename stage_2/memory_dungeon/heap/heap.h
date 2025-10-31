#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>  
/* Common definitions handler, doesn't do anything itself but allows us access to size_t, 
an unsigned integer type returned by the size of operator.*/

/*For reference, signed integers can represent non-negative AND negative numbers, 
whereas unsigned integers can only represent non-negative integers.
size_t is the standard type used for object sizes and array indexing.
It's an unsigned integer because memory addresses can never be negative by definition,
and size_t can thus represent the widest array of addresses that way.*/


void heap_init();
void *heap_alloc(size_t size);
void heap_dump();
void run_heap_demo();


#endif