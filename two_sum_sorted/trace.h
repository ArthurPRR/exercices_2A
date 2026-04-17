#ifndef TWO_SUM_SORTED_TRACE_H
#define TWO_SUM_SORTED_TRACE_H

#define TS_TRACE_CAP 64

typedef struct {
    int reads;
    int indices[TS_TRACE_CAP];
} ts_trace_t;

extern ts_trace_t ts_trace;

static inline void ts_trace_reset(void)
{
    ts_trace.reads = 0;
}

static inline int ts_read(const int arr[], int idx)
{
    if (ts_trace.reads < TS_TRACE_CAP)
        ts_trace.indices[ts_trace.reads] = idx;
    ts_trace.reads++;
    return arr[idx];
}

#endif