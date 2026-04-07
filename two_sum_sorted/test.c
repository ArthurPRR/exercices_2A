#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern int two_sum_sorted(int len, int arr[len], int target);

static int two_sum_sorted_corr(int len, int arr[], int target)
{
    if (len <= 1)
        return 0;

    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target)
            return 1;
        if (sum < target)
            left++;
        else
            right--;
    }
    return 0;
}

static void run_test(int len, int input[len], int target, int expected, int *passed, int *total)
{
    (*total)++;

    int sz = len > 0 ? len : 1;
    int stu[sz], corr[sz];
    for (int i = 0; i < len; i++) {
        stu[i] = input[i];
        corr[i] = input[i];
    }

    int res_stu = two_sum_sorted(len, stu, target);
    int res_corr = two_sum_sorted_corr(len, corr, target);
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
    run_test(0, test1, 5, 0, &passed, &total);

    int test2[] = {1, 2, 3, 4, 5};
    run_test(5, test2, 9, 1, &passed, &total);

    int test3[] = {1, 2, 3, 4, 5};
    run_test(5, test3, 10, 0, &passed, &total);

    int test4[] = {-10, -3, 0, 4, 9, 12};
    run_test(6, test4, 6, 1, &passed, &total);

    int test5[] = {-10, -3, 0, 4, 9, 12};
    run_test(6, test5, 100, 0, &passed, &total);

    int test6[] = {2, 2, 3, 4, 7, 11};
    run_test(6, test6, 4, 1, &passed, &total);

    int test7[] = {2, 2, 3, 4, 7, 11};
    run_test(6, test7, 20, 0, &passed, &total);

    int test8[] = {-8, -5, -2, 1, 4, 9};
    run_test(6, test8, -1, 1, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
