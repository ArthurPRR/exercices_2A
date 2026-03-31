#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern void selection_sort(int len, int arr[len]);

static void selection_sort_corr(int len, int arr[])
{
    if (len <= 0)
        return;
    for (int i = 0; i < len - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i) {
            int tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

static void run_test(int len, int input[len], int *passed, int *total)
{
    (*total)++;

    int sz = len > 0 ? len : 1;
    int stu[sz], corr[sz];
    for (int i = 0; i < len; i++) {
        stu[i] = input[i];
        corr[i] = input[i];
    }

    selection_sort(len, stu);
    selection_sort_corr(len, corr);

    int ok = 1;
    for (int i = 0; i < len; i++) {
        if (stu[i] != corr[i]) {
            ok = 0;
            break;
        }
    }

    if (ok) {
        (*passed)++;
    } else {
        printf(RED "Test %d FAILED\n" RESET, *total);
        printf("Expected: ");
        for (int i = 0; i < len; i++)
            printf("%d ", corr[i]);
        printf("\nGot: ");
        for (int i = 0; i < len; i++)
            printf("%d ", stu[i]);
        printf("\n");
    }
}

int main(void)
{
    int passed = 0, total = 0;

    // Test 1: Empty array
    int test1[] = {};
    run_test(0, test1, &passed, &total);

    // Test 2: Single element
    int test2[] = {42};
    run_test(1, test2, &passed, &total);

    // Test 3: Already sorted
    int test3[] = {1, 2, 3, 4, 5};
    run_test(5, test3, &passed, &total);

    // Test 4: Unsorted array
    int test4[] = {5, 2, 8, 1, 9};
    run_test(5, test4, &passed, &total);

    // Test 5: Reverse sorted
    int test5[] = {5, 4, 3, 2, 1};
    run_test(5, test5, &passed, &total);

    // Test 6: Duplicates
    int test6[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    run_test(9, test6, &passed, &total);

    // Test 7: Negative numbers
    int test7[] = {-5, 3, -1, 0, -10, 5};
    run_test(6, test7, &passed, &total);

    // Test 8: Large array
    int test8[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    run_test(10, test8, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
