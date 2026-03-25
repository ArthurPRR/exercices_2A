#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

static void check(int condition, const char *desc, int *passed, int *total)
{
    (*total)++;
    if (condition) {
        (*passed)++;
    } else {
        printf(RED "Test %d FAILED: %s\n" RESET, *total, desc);
    }
}

int main()
{
    int passed = 0;
    int total = 0;

    /* Empty list */
    node_t *list = NULL;
    check(list_length(list) == 0,         "length of empty list is 0",           &passed, &total);
    check(list_contains(list, 42) == 0,   "empty list does not contain 42",      &passed, &total);
    list = list_free(list);
    check(list == NULL,                   "free of empty list returns NULL",      &passed, &total);

    /* Single element */
    list = list_insert(NULL, 10);
    check(list != NULL,                   "insert into empty list returns non-NULL", &passed, &total);
    check(list_length(list) == 1,         "length after one insert is 1",        &passed, &total);
    check(list_contains(list, 10) == 1,   "list contains inserted value 10",     &passed, &total);
    check(list_contains(list, 99) == 0,   "list does not contain 99",            &passed, &total);
    list = list_free(list);
    check(list == NULL,                   "free of single-element list returns NULL", &passed, &total);

    /* Multiple elements */
    list = NULL;
    list = list_insert(list, 1);
    list = list_insert(list, 2);
    list = list_insert(list, 3);
    check(list_length(list) == 3,         "length after 3 inserts is 3",         &passed, &total);
    check(list_contains(list, 1) == 1,    "list contains 1",                     &passed, &total);
    check(list_contains(list, 2) == 1,    "list contains 2",                     &passed, &total);
    check(list_contains(list, 3) == 1,    "list contains 3",                     &passed, &total);
    check(list_contains(list, 4) == 0,    "list does not contain 4",             &passed, &total);
    list = list_free(list);
    check(list == NULL,                   "free of 3-element list returns NULL", &passed, &total);

    /* Duplicate values */
    list = NULL;
    list = list_insert(list, 5);
    list = list_insert(list, 5);
    list = list_insert(list, 5);
    check(list_length(list) == 3,         "length with duplicates is 3",         &passed, &total);
    check(list_contains(list, 5) == 1,    "list contains duplicate value 5",     &passed, &total);
    list = list_free(list);
    check(list == NULL,                   "free after duplicates returns NULL",   &passed, &total);

    /* Negative values */
    list = NULL;
    list = list_insert(list, -1);
    list = list_insert(list, -2);
    check(list_length(list) == 2,         "length with negatives is 2",          &passed, &total);
    check(list_contains(list, -1) == 1,   "list contains -1",                    &passed, &total);
    check(list_contains(list, -2) == 1,   "list contains -2",                    &passed, &total);
    check(list_contains(list, 0) == 0,    "list does not contain 0",             &passed, &total);
    list = list_free(list);
    check(list == NULL,                   "free after negatives returns NULL",    &passed, &total);

    /* Larger list */
    list = NULL;
    for (int i = 0; i < 10; i++)
        list = list_insert(list, i * 3);
    check(list_length(list) == 10,        "length of 10-element list is 10",     &passed, &total);
    check(list_contains(list, 0) == 1,    "large list contains 0",               &passed, &total);
    check(list_contains(list, 27) == 1,   "large list contains 27",              &passed, &total);
    check(list_contains(list, 1) == 0,    "large list does not contain 1",       &passed, &total);
    list = list_free(list);
    check(list == NULL,                   "free of large list returns NULL",      &passed, &total);

    printf("\n");

    if (passed == total)
        printf(GREEN "[%d/%d]: tests passed! Well Done\n" RESET, passed, total);
    else
        printf(RED "[%d/%d]: tests passed\n" RESET, passed, total);

    return (passed == total) ? 0 : 1;
}
