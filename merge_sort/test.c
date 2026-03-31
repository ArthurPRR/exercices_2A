#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

extern void merge_sort(int len, int arr[len]);

static void merge(int arr[], int left, int mid, int right)
{
    int left_len = mid - left + 1;
    int right_len = right - mid;
    
    int left_part[left_len], right_part[right_len];
    for (int i = 0; i < left_len; i++)
        left_part[i] = arr[left + i];
    for (int i = 0; i < right_len; i++)
        right_part[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < left_len && j < right_len) {
        if (left_part[i] <= right_part[j])
            arr[k++] = left_part[i++];
        else
            arr[k++] = right_part[j++];
    }
    while (i < left_len)
        arr[k++] = left_part[i++];
    while (j < right_len)
        arr[k++] = right_part[j++];
}

static void merge_sort_corr_helper(int arr[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_corr_helper(arr, left, mid);
        merge_sort_corr_helper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

static void merge_sort_corr(int len, int arr[])
{
    if (len <= 0)
        return;
    merge_sort_corr_helper(arr, 0, len - 1);
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

    merge_sort(len, stu);
    merge_sort_corr(len, corr);

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
