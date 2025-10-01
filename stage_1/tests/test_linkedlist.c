#include "linked_list.h"
#include <stdlib.h>   // malloc, free
#include <stdio.h>    // optional, for debug/error printing
#include <string.h>

int main(void){
    list_t *list = list_init(sizeof(int)); //Initialize list

    //Push integers 0-9 into list
    for (int i = 0; i < 10; i++){
        list_push_back(list, &i);
    };

    //Print the list in its original order (helper loop with list_get).
    printf("Original order:\n");
    for (size_t i=0; i < list->length; i++){
        int value;
        list_get(list, i, &value);
        printf("Node %zu has a value of %d\n", i, value);
    };

    // Set index 3 to 999 using list_set
    int new_value = 999;
    list_set(list, 3, &new_value);
    int check_value;
    list_get(list, 3, &check_value);
    printf("\nAfter list_set: Node 3 has value %d (expected 999)\n", check_value);

    // Reverse list with list_reverse.
    list_reverse(list);
    // Print again to confirm order is flipped.
    printf("Reversed order:\n");
    for (size_t i=0; i < list->length; i++){
        int value;
        list_get(list, i, &value);
        printf("Node %zu has a value of %d\n", i, value);
    };

    // Remove index 5 using list_remove
    list_remove(list, 5);
    printf("\nAfter list_remove at index 5:\n");
    for (size_t i = 0; i < list->length; i++){
        int value;
        list_get(list, i, &value);
        printf("Node %zu has a value of %d\n", i, value);
    };
    // Clean up with list_free.
    list_free(list);
    // Drop in the 🎉 Easter egg print: 
    printf("Your FAANG offer is in the mail. Congrats!\n");
    return 0;
};