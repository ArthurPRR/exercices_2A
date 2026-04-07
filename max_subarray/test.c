#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern int max_subarray(int len, int arr[len]);

static int max_subarray_corr(int len, int arr[])
{
    if (len <= 0)
        return 0;

    int best = arr[0];
    int current = arr[0];
    for (int i = 1; i < len; i++) {
        if (current < 0)
            current = arr[i];
        else
            current += arr[i];
        if (current > best)
            best = current;
    }
    return best;
}

static void run_test(int len, int input[len], int expected, int *passed, int *total)
{
    (*total)++;

    int sz = len > 0 ? len : 1;
    int stu[sz], corr[sz];
    for (int i = 0; i < len; i++) {
        stu[i] = input[i];
        corr[i] = input[i];
    }

    int res_stu = max_subarray(len, stu);
    int res_corr = max_subarray_corr(len, corr);
    int ok = (res_stu == expected && res_corr == expected);

    if (ok) {
        (*passed)++;
    } else {
        printf(RED "Test %d FAILED\n" RESET, *total);
        printf("Expected: %d\n", expected);
        printf("Got: %d\n", res_stu);
    }
}

int main(void)
{
    int passed = 0, total = 0;

    int test1[1] = {0};
    run_test(0, test1, 0, &passed, &total);

    int test2[] = {42};
    run_test(1, test2, 42, &passed, &total);

    int test3[] = {-5, -2, -9, -1};
    run_test(4, test3, -1, &passed, &total);

    int test4[] = {1, -2, 3, 4, -1, 2, 1, -5, 4};
    run_test(9, test4, 9, &passed, &total);

    int test5[] = {5, 4, -1, 7, 8};
    run_test(5, test5, 23, &passed, &total);

    int test6[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    run_test(9, test6, 6, &passed, &total);

    int test7[] = {0, 0, 0, 0};
    run_test(4, test7, 0, &passed, &total);

    int test8[] = {10, -3, 4, -2, 1, 6, -5, 4};
    run_test(8, test8, 16, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
