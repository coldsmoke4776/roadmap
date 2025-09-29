/*
 * vector.c
 * Implementation of a generic resizable array (vector).
 * Part of Stage 1: Data Structures & Utilities.
 */

#include "vector.h" // this is the header file that we're building with the function prototypes
#include <stdlib.h>  // malloc, realloc, free
#include <string.h>  // memcpy for copying elements
#include <stdio.h> //for stderr

//We defined the vector_t struct in vector.h, which is why need to inclide that file
//We're filling out the function body for a function we're calling vector_init that's going to return a pointer to a struct.
vector_t *vector_init(size_t element_size){
    if (element_size == 0){  // Error handling
        fprintf(stderr, "failed to initialize vector\n"); // If statement here checks for an empty element_size and prints an error if it finds one, returning NULL
        return NULL; 
    } else {
        vector_t *vec = malloc(sizeof(vector_t)); // if there is an element_size, we assign the various attributes to initialize the vector
        vec->element_size = element_size;
        vec->length = 0; // How many blocks are in use RIGHT NOW, length <= capacity must always be true.
        vec->capacity = 4; // How many blocks could the vector hold
        vec->data = malloc(vec->capacity * element_size);
        if (vec->data == NULL){
            free(vec);  // This frees the memory we allocated earlier in the else side of this if.else block
            return NULL; // If we're freeing up the memory, we don't need to return anything.
        }
        return vec; //returns pointer to vec struct
    }
}

/* This is freeing up the memory we're using for our vector here, otherwise we'll get memory leaks, 
we're passing in a pointer to *vec as an argument */
void vector_free(vector_t *vec){
    if (vec == NULL){
        fprintf(stderr, "failed to free memory for vector\n"); // This is error checking for whether there IS a vec struct to free memorty for
        return; // The type for this function is void, so it doesnt return anything at all.
    } else {
        free(vec->data); // We need to free the array first
        free(vec); // Then we free the struct itself
    }
    return; // The type for this function is void, so it doesnt return anything at all.
}

/*Purpose of this function is to append an element at the end.
If length == capacity, double the capacity and realloc before inserting.*/
void vector_push_back(vector_t *vec, void *element){
    // Defensive programming check to handle NULL input.
    if (vec == NULL || element == NULL){
        fprintf(stderr, "function failed to append element\n");
        return;
    }
    //Capacity check to handle the "If length == capacity, double the capacity and realloc before inserting" task
    if (vec->length == vec->capacity){
        vec->capacity = (vec->capacity) * 2; //Double capacity
        // Reallocate data
        void *new_data = realloc(vec->data, vec->capacity * vec->element_size);
        if (new_data == NULL){
            fprintf(stderr, "reallocation failed\n"); //Checking if reallocation failed
            return;
        }
        vec->data = new_data;
        // We don't know the size of data because its a void, so we can't do pointer arithmetic on it. So, we cast to char which advances in bytes.
    }
    void *destination = (char*)vec->data + (vec->length * vec->element_size); // Jump forward length * element_size bytes to find next free slot.
    memcpy(destination, element, vec->element_size); // Copy element_size bytes into that slot we just made.
    vec->length++; //Increment length
    return;
}

//Purpose of this function is to retrieve the element at a given index wand copy it into a caller-supplied pointer
void vector_get(vector_t *vec, size_t index, void *out_element){
    // Defensive programming check to handle NULL input
    if (vec == NULL){
        fprintf(stderr, "failed to retrieve given element\n");
        return;
    }
    // Defensive programming check to handle bounds checking for index
    if (index >= vec->length){
        fprintf(stderr, "out of bounds error\n");
        return;
    }
    // Defensive programming check to handle no destination pointer being provided.
    if (out_element == NULL){
        fprintf(stderr, "no destination pointer provided\n");
        return;
    }
    void *source = (char*)vec->data + index * vec->element_size; // Compute address of element slot. Cast to char to advance in bytes because we used void.
    memcpy(out_element, source, vec->element_size);
    return;
}

//Purpose of this function is to replace the element at a given index and replace it with new data.
void vector_set(vector_t *vec, size_t index, void *new_element){
    // Defensive programming check to handle NULL input
    if (vec == NULL){
        fprintf(stderr, "failed to retrieve given element\n");
        return;
    }
    // Defensive programming check to handle no new element to replace data with
    if (new_element == NULL){
        fprintf(stderr, "No new data to replace index data with\n");
        return;
    }
    // Defensive programming check to handle bounds checking for index
    if (index >= vec->length){
        fprintf(stderr, "out of bounds error\n");
        return;
    }
    void *destination = (char*)vec->data + index * vec->element_size; // Compute address of element slot. Cast to char to advance in  bytes because we used void
    memcpy(destination, new_element, vec->element_size);
    return;
}

