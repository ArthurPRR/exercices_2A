#include <stdio.h>
#include <stdlib.h>

#include "trace.h"

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

#define LARGE_LEN 1000000

extern int binary_search(int len, int arr[len], int target);

bs_trace_t bs_trace = {0};

static int binary_search_corr(int len, int arr[len], int target)
{
    if (len <= 0)
        return -1;
    int lo = 0, hi = len - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

static int binary_search_expected_trace(int len, int arr[len], int target, int indices[BS_TRACE_CAP])
{
    if (len <= 0)
        return 0;

    int lo = 0, hi = len - 1;
    int count = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (count < BS_TRACE_CAP)
            indices[count] = mid;
        count++;

        if (arr[mid] == target)
            return count;
        else if (arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return count;
}

static void run_test(int len, int arr[len], int target, int *passed, int *total)
{
    (*total)++;

    bs_trace_reset();

    int res_stu = binary_search(len, arr, target);
    int res_corr = binary_search_corr(len, arr, target);
    int expected_trace[BS_TRACE_CAP];
    int expected_reads = binary_search_expected_trace(len, arr, target, expected_trace);

    /* Accept any valid index pointing to the target value,
       or -1 when the target is absent. */
    int ok;
    if (res_corr == -1) {
        ok = (res_stu == -1);
    } else {
        ok = (res_stu >= 0 && res_stu < len && arr[res_stu] == target);
    }

    if (ok) {
        ok = (bs_trace.reads == expected_reads);
        for (int i = 0; ok && i < expected_reads; i++) {
            if (bs_trace.indices[i] != expected_trace[i])
                ok = 0;
        }
    }

    if (ok) {
        (*passed)++;
    } else {
        printf(RED "Test %d FAILED\n" RESET, *total);
        if (res_corr == -1)
            printf("Expected: -1 (not found)\n");
        else
            printf("Expected: a valid index i such that arr[i] == %d\n", target);
        printf("Received: %d\n", res_stu);
        printf("Trace reads: %d\n", bs_trace.reads);
        printf("Expected trace: ");
        for (int i = 0; i < expected_reads; i++)
            printf("%d ", expected_trace[i]);
        printf("\nReceived trace: ");
        for (int i = 0; i < bs_trace.reads && i < BS_TRACE_CAP; i++)
            printf("%d ", bs_trace.indices[i]);
        printf("\n\n");
    }
}

int main()
{
    int passed = 0;
    int total = 0;

    int arr1[] = {1, 3, 5, 7, 9};
    run_test(5, arr1, 5,  &passed, &total);  /* middle */
    run_test(5, arr1, 1,  &passed, &total);  /* first element */
    run_test(5, arr1, 9,  &passed, &total);  /* last element */
    run_test(5, arr1, 4,  &passed, &total);  /* not found (between values) */
    run_test(5, arr1, 0,  &passed, &total);  /* not found (below range) */
    run_test(5, arr1, 10, &passed, &total);  /* not found (above range) */

    int arr2[] = {42};
    run_test(1, arr2, 42, &passed, &total);  /* single element, found */
    run_test(1, arr2,  0, &passed, &total);  /* single element, not found */

    int arr3[] = {};
    run_test(0, arr3, 5, &passed, &total);   /* empty array */

    int arr4[] = {-10, -5, 0, 5, 10, 15, 20};
    run_test(7, arr4, -10, &passed, &total); /* negative, found at start */
    run_test(7, arr4,  15, &passed, &total); /* found near end */
    run_test(7, arr4,   7, &passed, &total); /* not found */

    int *arr5 = malloc(sizeof(int) * LARGE_LEN);
    if (arr5 != NULL) {
        for (int i = 0; i < LARGE_LEN; i++)
            arr5[i] = i * 2;
        run_test(LARGE_LEN, arr5, -1, &passed, &total);
        free(arr5);
    }

    printf("\n");

    if (passed == total)
        printf(GREEN "[%d/%d]: tests passed! Well Done\n" RESET, passed, total);
    else
        printf(RED "[%d/%d]: tests passed\n" RESET, passed, total);

    return (passed == total) ? 0 : 1;
}
