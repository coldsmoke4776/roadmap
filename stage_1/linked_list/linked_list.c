#include "linked_list.h"
#include <stdlib.h>   // malloc, free
#include <stdio.h>    // optional, for debug/error printing
#include <string.h>


//Purpose of the function is to initialize a list
// We pass void here because we don't have an existing list, we're creating one
list_t *list_init(size_t element_size){
    list_t *list = malloc(sizeof(list_t)); // We need to allocate memory for the list we're initializing
    //defensive programming check for NULL 
    if (list == NULL){
        fprintf(stderr, "failed to allocate memory for list\n");
        return NULL;
    }
    list->head = NULL; // Set head to NULL (initial state)
    list->length= 0; // Set length to 0, because it's an int (initial state)
    list->element_size = element_size; // Utilize element_size
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
        free(current->data); // Free the element's memory first
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
    // Allocate space for the actual element
    front_node->data = malloc(list->element_size); // Setting content of front_node
    //Defensive programming check for failed allocation for element
    if (front_node->data == NULL){
        free(front_node);
        fprintf(stderr,"Operation failed: allocation for element\n");
        return;
    }
    // Copy element into node's own memory now that it's been allocated
    memcpy(front_node->data, element, list->element_size);
    //Link it in
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
    // Defensive programming check to handle NULL (no allocation for back_node)
    if(back_node == NULL){
        fprintf(stderr, "Operation failed, no allocation for back_node\n");
        return;
    }
    // Allocate space for the actual element
    back_node->data = malloc(list->element_size); // Setting content of back_node
    //Defensive programming check for failed allocation for element
    if (back_node->data == NULL){
        free(back_node);
        fprintf(stderr,"Operation failed: allocation for element\n");
        return;
    }
    // Copy element into node's own memory now that it's been allocated
    memcpy(back_node->data, element, list->element_size);
    //Link it in
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
        current->next = back_node; // Adding our back_node to the end of the linked list
    }
    list->length++; // Increment list length
    return;
};

// Purpose of this function is to retrive the element at a given index node of the list
void list_get(list_t *list, size_t index, void *out_element){
    //Defensive programming check for NULL - no list
    if (list == NULL){
        fprintf(stderr, "Operation failed: no list to retrieve from\n");
        return;
    }
    // Defensive programming check for out of bounds check re: index
    if (index >= list->length){
        fprintf(stderr, "Operation failed: out of bounds error for index and list\n");
        return;
    }
    //Defensive programming check for nowhere to copy element to
    if (out_element == NULL){
        fprintf(stderr, "Operation failed: nowhere to copy element to\n");
        return;
    }
    node_t *current = list->head; // Set current node to head of the list
    size_t i = 0;
    while(i <index){
        current = current->next;
        i++;
    }
    memcpy(out_element, current->data, list->element_size);
    return;
};

//Purpose of this function is to replace the content at a given index node with new_element
void list_set(list_t *list, size_t index, void *new_element){
     //Defensive programming check for NULL - no list
     if (list == NULL){
        fprintf(stderr, "Operation failed: no list to retrieve from\n");
        return;
    }
    // Defensive programming check for out of bounds check re: index
    if (index >= list->length){
        fprintf(stderr, "Operation failed: out of bounds error for index and list\n");
        return;
    }
    //Defensive programming check for nothing to copy into index element
    if (new_element == NULL){
        fprintf(stderr, "Operation failed: nothing to copy into set node\n");
        return;
    }
    node_t *current = list->head; // Set current node to the head of the list
    size_t i = 0;
    while (i < index){
        current = current->next; // Walk the nodes until we get to the desired index node
        i++;
    }
    memcpy(current->data, new_element, list->element_size); // Copy the new element into the data portion of the current node
    return;
};

// Purpose of this function is to remove the node at a given index of the list from it
void list_remove(list_t*list, size_t index){
      //Defensive programming check for NULL - no list
      if (list == NULL){
        fprintf(stderr, "Operation failed: no list to retrieve from\n");
        return;
    }
    // Defensive programming check for out of bounds check re: index
    if (index >= list->length){
        fprintf(stderr, "Operation failed: out of bounds error for index and list\n");
        return;
    }
    node_t *current = list->head; //Set the current node to the head of the list
    if (index == 0){
        node_t *removed_node = list->head; // Save old head so you don't lose the pointer
        list->head = removed_node->next; // Bump head along
        free(removed_node->data);
        free(removed_node);
    } else {
        size_t i = 0;
        while(i < (index-1)){
            current = current->next; // Walk the nodes
            i++;
        }
        // Change that node’s next pointer to skip the node being removed.
        node_t *removed_node = current->next;
        current->next = removed_node->next; // Skip over this node
        free(removed_node->data);
        free(removed_node);
    }
    list->length--;//Decrement list-> length
    return;
};

//Purpose of this function is to get a job at a FAANG company as an SWE.
// Jokes aside, the purpose of this function is to reverse the linked list in direction.
void list_reverse(list_t *list){
    //Defensive programming check for NULL - no list
    if (list == NULL){
        fprintf(stderr, "Operation failed: no list to retrieve from\n");
        return;
    }
    //Create three pointers to juggle for reversing the list
    node_t *prev = NULL; // At the start, there is no "before" so prev starts as NULL
    node_t *current = list->head; //Set the current node to the head of the list
    while (current != NULL){
        node_t *next = current->next; // Next node in the chain
        current->next = prev;
        prev = current; // Slide prev forward
        current = next; // Slide current forward
    }
    list->head = prev; // After loop, prev is now head of the list, because it's backwards now!
    return;
};
