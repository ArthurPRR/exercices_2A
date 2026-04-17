#include <stdio.h>
#include <stdlib.h>

#include "trace.h"

// Return 1 if two distinct elements in the sorted array sum to 'target'.
// Return 0 otherwise or if the input is invalid.
//
// Instrumentation requirement:
// - Call ts_trace_reset() once at the beginning of your function.
// - Read elements with ts_read(arr, index) instead of arr[index].
// The tests use this trace to verify the pointer movement.

int two_sum_sorted(int len, int arr[len], int target) {
    (void)len;
    (void)arr;
    (void)target;
    return 0;
}
