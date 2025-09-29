#include "vector.h"
#include <stdio.h>

//entry point for program
int main(void){
    //cal vector_init to initialize vector
    vector_t *vec = vector_init(sizeof(int));
    // check it worked - if vector_init didn't work, vec will be NULL
    if (vec == NULL){
        fprintf(stderr, "allocation for vector failed\n");
        return 1;
    }
    // print some fields
    printf("Vector Field 1: Length is %zu\n", vec->length); // %zu is the identifier for size_t, not %d like I thought before
    printf("Vector Field 2: Capacity is %zu\n", vec->capacity); // %zu is the identifier for size_t, not %d like I thought before

    //push some ints into vector
    for (int i = 0; i<10 ; i++){
        vector_push_back(vec, &i); //We want to push the address of i.
        printf("Pushed %d, length %zu + capacity %zu\n", i, vec->length, vec->capacity);
    }

    // read back the values - we want to see if they're stored properly.
    /*for (size_t i = 0; i < vec->length; i++){
        // We need to compute the pointer to whatever the ith element is
        int *value = (int*)((char*)vec->data + i * vec->element_size);
        printf("vec[%d] = %d\n", i, *value);
    }*/

    //Test to see if vector_get works
    printf("Testing vector_get\n");
    for (size_t i = 0; i < vec->length; i++){
        int value;
        vector_get(vec, i, &value);
        printf("vec[%zu]: %d\n", i, value);
    }

    //Test if vector_set works by changing a number at a given index
    printf("Testing vector_set\n");
    int new_value = 999;
    vector_set(vec, 3, &new_value);

    //Confirm overwrite
    printf("Confirming overwrite\n");
    int check_value;
    vector_get(vec, 3, &check_value);
    printf("After set: vec[3]: %d (expected 999)\n", check_value);

    // call vector_free
    vector_free(vec);
    return 0;
}