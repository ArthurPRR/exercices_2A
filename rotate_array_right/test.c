#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern void rotate_array_right(int len, int arr[len], int k);

static void reverse(int arr[], int left, int right)
{
    while (left < right) {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;
        left++;
        right--;
    }
}

static void rotate_array_right_corr(int len, int arr[], int k)
{
    if (len <= 0)
        return;

    k %= len;
    if (k < 0)
        k += len;
    if (k == 0)
        return;

    reverse(arr, 0, len - 1);
    reverse(arr, 0, k - 1);
    reverse(arr, k, len - 1);
}

static void run_test(int len, int input[len], int k, int *passed, int *total)
{
    (*total)++;

    int sz = len > 0 ? len : 1;
    int stu[sz], corr[sz];
    for (int i = 0; i < len; i++) {
        stu[i] = input[i];
        corr[i] = input[i];
    }

    rotate_array_right(len, stu, k);
    rotate_array_right_corr(len, corr, k);

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

    int test1[1] = {0};
    run_test(0, test1, 3, &passed, &total);

    int test2[] = {1};
    run_test(1, test2, 5, &passed, &total);

    int test3[] = {1, 2, 3, 4, 5};
    run_test(5, test3, 2, &passed, &total);

    int test4[] = {1, 2, 3, 4, 5};
    run_test(5, test4, 7, &passed, &total);

    int test5[] = {-1, -100, 3, 99};
    run_test(4, test5, 1, &passed, &total);

    int test6[] = {10, 20, 30, 40, 50, 60};
    run_test(6, test6, -1, &passed, &total);

    int test7[] = {9, 8, 7, 6, 5, 4, 3};
    run_test(7, test7, 14, &passed, &total);

    int test8[] = {1, 2, 3, 4, 5, 6, 7, 8};
    run_test(8, test8, 0, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
