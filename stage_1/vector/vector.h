/*
 * vector.c
 * Implementation of a generic resizable array (vector).
 * Part of Stage 1: Data Structures & Utilities.
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>  // for size_t
#include <stdio.h> //for stderr

typedef struct {
    void *data; // pointer to actual data within the array.
    size_t element_size;
    size_t length;
    size_t capacity;
} vector_t;

vector_t *vector_init(size_t element_size);
void vector_free(vector_t *vec);
void vector_push_back(vector_t *vec, void *element);
void vector_get(vector_t *vec, size_t index, void *out_element);
void vector_set(vector_t *vec, size_t index, void *new_element);



#endif
