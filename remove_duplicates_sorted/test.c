#include <stdio.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern int remove_duplicates_sorted(int len, int arr[len]);

static int remove_duplicates_sorted_corr(int len, int arr[])
{
    if (len <= 0)
        return 0;

    int write = 1;
    for (int read = 1; read < len; read++) {
        if (arr[read] != arr[write - 1])
            arr[write++] = arr[read];
    }
    return write;
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

    int new_len_stu = remove_duplicates_sorted(len, stu);
    int new_len_corr = remove_duplicates_sorted_corr(len, corr);

    int ok = (new_len_stu == new_len_corr);
    if (ok) {
        for (int i = 0; i < new_len_corr; i++) {
            if (stu[i] != corr[i]) {
                ok = 0;
                break;
            }
        }
    }

    if (ok) {
        (*passed)++;
    } else {
        printf(RED "Test %d FAILED\n" RESET, *total);
        printf("Expected length: %d\n", new_len_corr);
        printf("Got length: %d\n", new_len_stu);
    }
}

int main(void)
{
    int passed = 0, total = 0;

    int test1[1] = {0};
    run_test(0, test1, &passed, &total);

    int test2[] = {1};
    run_test(1, test2, &passed, &total);

    int test3[] = {1, 1, 2, 2, 3, 3, 3, 4};
    run_test(8, test3, &passed, &total);

    int test4[] = {-5, -5, -2, 0, 0, 1, 1, 9};
    run_test(8, test4, &passed, &total);

    int test5[] = {1, 2, 3, 4, 5};
    run_test(5, test5, &passed, &total);

    int test6[] = {7, 7, 7, 7, 7};
    run_test(5, test6, &passed, &total);

    int test7[] = {1, 2, 2, 3, 4, 4, 5, 5, 5, 6};
    run_test(10, test7, &passed, &total);

    int test8[] = {-3, -1, 0, 2, 4, 4, 4, 8};
    run_test(8, test8, &passed, &total);

    printf(GREEN "%d/%d tests passed\n" RESET, passed, total);
    return passed == total ? 0 : 1;
}
