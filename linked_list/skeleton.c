#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Insert 'value' at the head of the list. Returns the new head.
node_t *list_insert(node_t *head, int value) {
    (void)value;
    return head;
}

// Return the number of nodes in the list.
int list_length(node_t *head) {
    (void)head;
    return 0;
}

// Return 1 if 'value' is in the list, 0 otherwise.
int list_contains(node_t *head, int value) {
    (void)head;
    (void)value;
    return 0;
}

// Free all nodes in the list. Returns NULL.
node_t *list_free(node_t *head) {
    (void)head;
    return NULL;
}
