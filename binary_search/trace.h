#ifndef BINARY_SEARCH_TRACE_H
#define BINARY_SEARCH_TRACE_H

#define BS_TRACE_CAP 64

typedef struct {
    int reads;
    int indices[BS_TRACE_CAP];
} bs_trace_t;

extern bs_trace_t bs_trace;

static inline void bs_trace_reset(void)
{
    bs_trace.reads = 0;
}

static inline int bs_read(const int arr[], int idx)
{
    if (bs_trace.reads < BS_TRACE_CAP)
        bs_trace.indices[bs_trace.reads] = idx;
    bs_trace.reads++;
    return arr[idx];
}

#endif