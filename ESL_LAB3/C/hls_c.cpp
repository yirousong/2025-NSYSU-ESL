#include <ap_int.h>

void rgb2yuv_axi(
    volatile int *r,
    volatile int *g,
    volatile int *b,
    volatile int *y,
    volatile int *u,
    volatile int *v)
{
#pragma HLS INTERFACE s_axilite port = r
#pragma HLS INTERFACE s_axilite port = g
#pragma HLS INTERFACE s_axilite port = b
#pragma HLS INTERFACE s_axilite port = y
#pragma HLS INTERFACE s_axilite port = u
#pragma HLS INTERFACE s_axilite port = v
#pragma HLS INTERFACE s_axilite port = return

    *y = 0.299 * (*r) + 0.587 * (*g) + 0.114 * (*b);
    *u = -0.169 * (*r) - 0.331 * (*g) + 0.5 * (*b) + 128;
    *v = 0.5 * (*r) - 0.419 * (*g) - 0.081 * (*b) + 128;
}
