#include <stdio.h>
#include <stdlib.h>

#include "trace.h"

// Perform a binary search on the sorted array 'arr' of length 'len'.
// Return the index of 'target' if found, -1 if not found or if input is invalid.
//
// Instrumentation requirement:
// - Call bs_trace_reset() once at the beginning of your function.
// - Read elements with bs_read(arr, index) instead of arr[index].
// The tests use this trace to verify the search path.

int binary_search(int len, int arr[len], int target) {
    (void)len;
    (void)arr;
    (void)target;
    return -1;
}
