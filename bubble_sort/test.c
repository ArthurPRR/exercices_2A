#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern void bubble_sort(int len, int arr[len]);

static void bubble_sort_corr(int len, int arr[])
{
    if (len <= 0)
        return;
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
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

    bubble_sort(len, stu);
    bubble_sort_corr(len, corr);

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
        printf("Expected: [");
        for (int i = 0; i < len; i++)
            printf("%d%s", corr[i], i < len - 1 ? ", " : "");
        printf("]\n");
        printf("Received: [");
        for (int i = 0; i < len; i++)
            printf("%d%s", stu[i], i < len - 1 ? ", " : "");
        printf("]\n\n");
    }
}

int main()
{
    int passed = 0;
    int total = 0;

    int arr1[] = {5, 3, 1, 4, 2};
    run_test(5, arr1, &passed, &total);

    int arr2[] = {1, 2, 3, 4, 5};
    run_test(5, arr2, &passed, &total);

    int arr3[] = {5, 4, 3, 2, 1};
    run_test(5, arr3, &passed, &total);

    int arr4[] = {42};
    run_test(1, arr4, &passed, &total);

    int arr5[] = {3, 3, 3, 3};
    run_test(4, arr5, &passed, &total);

    int arr6[] = {-3, -1, -4, -1, -5};
    run_test(5, arr6, &passed, &total);

    int arr7[] = {-2, 7, 0, -5, 3};
    run_test(5, arr7, &passed, &total);

    int arr8[] = {};
    run_test(0, arr8, &passed, &total);

    int arr9[] = {4, 2, 4, 1, 2};
    run_test(5, arr9, &passed, &total);

    int arr10[] = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    run_test(10, arr10, &passed, &total);

    printf("\n");

    if (passed == total)
        printf(GREEN "[%d/%d]: tests passed! Well Done\n" RESET, passed, total);
    else
        printf(RED "[%d/%d]: tests passed\n" RESET, passed, total);

    return (passed == total) ? 0 : 1;
}
