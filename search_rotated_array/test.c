#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern int search_rotated_array(int len, int arr[len], int target);

static int search_rotated_array_corr(int len, int arr[], int target)
{
    if (len <= 0)
        return -1;

    int left = 0;
    int right = len - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;

        if (arr[left] <= arr[mid]) {
            if (arr[left] <= target && target < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;
        } else {
            if (arr[mid] < target && target <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}

static void run_test(int len, int input[len], int target, int *passed, int *total)
{
    (*total)++;

    int sz = len > 0 ? len : 1;
    int stu[sz], corr[sz];
    for (int i = 0; i < len; i++) {
        stu[i] = input[i];
        corr[i] = input[i];
    }

    int res_stu = search_rotated_array(len, stu, target);
    int res_corr = search_rotated_array_corr(len, corr, target);

    int ok;
    if (res_corr == -1) {
        ok = (res_stu == -1);
    } else {
        ok = (res_stu >= 0 && res_stu < len && stu[res_stu] == target);
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

    int test1[1] = {0};
    run_test(0, test1, 5, &passed, &total);

    int test2[] = {4, 5, 6, 7, 0, 1, 2};
    run_test(7, test2, 0, &passed, &total);

    int test3[] = {4, 5, 6, 7, 0, 1, 2};
    run_test(7, test3, 3, &passed, &total);

    int test4[] = {1, 2, 3, 4, 5, 6, 7};
    run_test(7, test4, 4, &passed, &total);

    int test5[] = {6, 7, 1, 2, 3, 4, 5};
    run_test(7, test5, 6, &passed, &total);

    int test6[] = {30, 40, 50, 10, 20};
    run_test(5, test6, 20, &passed, &total);

    int test7[] = {30, 40, 50, 10, 20};
    run_test(5, test7, 35, &passed, &total);

    int test8[] = {9, 10, 11, 12, 1, 2, 3, 5, 7};
    run_test(9, test8, 12, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
