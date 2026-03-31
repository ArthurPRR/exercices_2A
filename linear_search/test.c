#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern int linear_search(int len, int arr[len], int target);

static int linear_search_corr(int len, int arr[len], int target)
{
    if (len <= 0)
        return -1;
    for (int i = 0; i < len; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

static void run_test(int len, int arr[len], int target, int *passed, int *total)
{
    (*total)++;

    int res_stu = linear_search(len, arr, target);
    int res_corr = linear_search_corr(len, arr, target);

    /* Accept -1 when target is not found,
       or the first valid index pointing to the target value. */
    int ok;
    if (res_corr == -1) {
        ok = (res_stu == -1);
    } else {
        ok = (res_stu >= 0 && res_stu < len && arr[res_stu] == target);
    }

    if (ok) {
        (*passed)++;
    } else {
        printf(RED "Test %d FAILED\n" RESET, *total);
        if (res_corr == -1)
            printf("Expected: -1 (not found)\n");
        else
            printf("Expected: a valid index i such that arr[i] == %d\n", target);
        printf("Got: %d\n", res_stu);
    }
}

int main(void)
{
    int passed = 0, total = 0;

    // Test 1: Empty array
    int test1[] = {};
    run_test(0, test1, 5, &passed, &total);

    // Test 2: Single element - found
    int test2[] = {42};
    run_test(1, test2, 42, &passed, &total);

    // Test 3: Single element - not found
    int test3[] = {42};
    run_test(1, test3, 10, &passed, &total);

    // Test 4: Target at beginning
    int test4[] = {5, 2, 8, 1, 9};
    run_test(5, test4, 5, &passed, &total);

    // Test 5: Target at end
    int test5[] = {5, 2, 8, 1, 9};
    run_test(5, test5, 9, &passed, &total);

    // Test 6: Target in middle
    int test6[] = {5, 2, 8, 1, 9};
    run_test(5, test6, 8, &passed, &total);

    // Test 7: Target not found
    int test7[] = {5, 2, 8, 1, 9};
    run_test(5, test7, 10, &passed, &total);

    // Test 8: Duplicates - finds first occurrence
    int test8[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    run_test(9, test8, 1, &passed, &total);

    // Test 9: Negative numbers
    int test9[] = {-5, 3, -1, 0, -10, 5};
    run_test(6, test9, -10, &passed, &total);

    // Test 10: Zero as target
    int test10[] = {-5, 3, -1, 0, -10, 5};
    run_test(6, test10, 0, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
