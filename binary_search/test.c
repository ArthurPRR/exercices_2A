#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern int binary_search(int len, int arr[len], int target);

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

static void run_test(int len, int arr[len], int target, int *passed, int *total)
{
    (*total)++;

    int res_stu = binary_search(len, arr, target);
    int res_corr = binary_search_corr(len, arr, target);

    /* Accept any valid index pointing to the target value,
       or -1 when the target is absent. */
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
        printf("Received: %d\n\n", res_stu);
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

    printf("\n");

    if (passed == total)
        printf(GREEN "[%d/%d]: tests passed! Well Done\n" RESET, passed, total);
    else
        printf(RED "[%d/%d]: tests passed\n" RESET, passed, total);

    return (passed == total) ? 0 : 1;
}
