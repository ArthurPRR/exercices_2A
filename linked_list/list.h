#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

// Insert 'value' at the head of the list. Returns the new head.
node_t *list_insert(node_t *head, int value);

// Return the number of nodes in the list.
int list_length(node_t *head);

// Return 1 if 'value' is in the list, 0 otherwise.
int list_contains(node_t *head, int value);

// Free all nodes in the list. Returns NULL.
node_t *list_free(node_t *head);

#endif
