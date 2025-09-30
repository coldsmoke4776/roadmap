#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h> // for size_t


typedef struct node {
    void *data;
    struct node *next; // Points to next node in the list - hence LINKED list!
} node_t;

typedef struct {
    node_t *head;
    size_t length;
} list_t;

//Core API for the linked list
list_t *list_init(void);
void list_free(list_t *list);
void list_push_front(list_t *list, void *element);
void list_push_back(list_t *list, void *element);
void list_get(list_t *list, size_t index, void *out_element);
void list_set(list_t *list, size_t index, void *new_element);
void list_remove(list_t*list, size_t index);
void list_reverse(list_t *list);


#endif