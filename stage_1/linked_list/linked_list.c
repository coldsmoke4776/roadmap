#include "linked_list.h"
#include <stdlib.h>   // malloc, free
#include <stdio.h>    // optional, for debug/error printing

//Purpose of the function is to initialize a list
// We pass void here because we don't have an existing list, we're creating one
list_t *list_init(void){
    list_t *list = malloc(sizeof(list_t)); // We need to allocate memory for the list we're initializing
    //defensive programming check for NULL 
    if (list == NULL){
        fprintf(stderr, "failed to allocate memory for list\n");
        return NULL;
    }
    list->head = NULL; // Set head to NULL (initial state)
    list->length= 0; // Set length to 0, because it's an int (initial state)
    return list; // Return created list pointer
};

//Purpose of the function is to free the allocated memory for the list
// We pass the pointer to the list, because we don't want a copy, we want to free the list we created above
void list_free(list_t *list){
    // Defensive programming check for NULL
    if(list == NULL){
        fprintf(stderr,"list does not exist to free memory for\n");
        return;
    }
    node_t *current = list->head; // Set current job to top of list
    while(current != NULL){
        node_t *temp_node = current->next; // Walk the nodes by storing next job in a temp variable
        free(current); // Free current node
        current = temp_node; // Assign current node to temp_node to "walk the nodes"
    }
    free(list); // Free the whole list
    return; // Return nothing due to void.
};

//Purpose of the function is to add a new element to the front of the linked list
void list_push_front(list_t *list, void *element){
    // Defensive programming check to handle NULL (no list/element to push into or push)
    if(list == NULL){
        fprintf(stderr, "Operation failed, no list to push into\n");
        return;
    }
    if(element == NULL){
        fprintf(stderr, "Operation failed, no element to push\n");
        return;
    }
    node_t *front_node = malloc(sizeof(node_t)); // Allocate space for front_node
    //Defensive programming check for NULL (failed allocation for new node)
    if(front_node ==  NULL){
        fprintf(stderr, "Allocation failed for front_node\n");
        return;
    }
    front_node->data = element; // Setting content of front_node
    front_node->next = list->head; // Set front_node's next to current list's head
    list->head = front_node; // Set list's head to front_node
    list->length++; //Increment list's length
    return;
};

// Purpose of this function is to add a single element to the back of the linked list
void list_push_back(list_t *list, void *element){
    // Defensive programming check to handle NULL (no list to push into/element to push)
    if (list == NULL){
        fprintf(stderr, "Operation failed: No list to push into!\n");
        return;
    }
    if(element == NULL){
        fprintf(stderr, "Operation failed, no element to push\n");
        return;
    }
    node_t *back_node = malloc(sizeof(node_t)); // Allocate space in memory for back_node
    // Defensive programming check to ahndle NULL (no allocation for back_node)
    if(back_node == NULL){
        fprintf(stderr, "Operation failed, no allocation for back_node\n");
        return;
    }
    back_node->data = element; // Set back_node's content
    back_node->next = NULL; // NULL because this is the last node in the linked list
    // Check if list head is empty, and if so add back_node
    node_t *current = list->head; // Set current job to top of list
    if(list->head == NULL){
        list->head = back_node;
    } else {
        while (current->next != NULL){
            node_t *temp_node = current->next; // Walk the nodes by storing next job in a temp variable
            current = temp_node; // Assign current node to temp_node to "walk the nodes"
        }
    }
    current->next = back_node; // Adding our back_node to the end of the linked list
    list->length++; // Increment list length
    return;
};