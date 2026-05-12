#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

void fill_random(Matrix *m) {
    for (int i = 0; i < m->rows * m->cols; i++) {
        m->data[i] = (float)rand() / RAND_MAX * 10.0f;
    }
}

double benchmark(int rows_a, int cols_a, int cols_b, int runs) {
    Matrix a, b, result;
    mat_alloc(&a, rows_a, cols_a);
    mat_alloc(&b, cols_a, cols_b);
    fill_random(&a);
    fill_random(&b);

    struct timespec start, end;
    double total = 0.0;

    for (int r = 0; r < runs; r++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        mat_mul(&a, &b, &result);
        clock_gettime(CLOCK_MONOTONIC, &end);

        total += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        mat_free(&result);
    }

    mat_free(&a);
    mat_free(&b);
    return total / runs;
}

int main() {
    srand(42);

    typedef struct { int m, k, n; } Size;
    Size sizes[] = {
        {8,     8,     8},
        {32,    32,    32},
        {64,    64,    64},
        {128,   128,   128},
        {256,   256,   256},
        {512,   512,   512},
        {1024,  1024,  1024},
        {64,    512,   64},
        {512,   64,    512},
    };
    int n = sizeof(sizes) / sizeof(sizes[0]);

    printf("\n=== matrix multiplication benchmark ===\n\n");
    printf("%-22s %8s %12s %14s\n", "size (MxK * KxN)", "runs", "avg time", "MFLOPS");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int m = sizes[i].m;
        int k = sizes[i].k;
        int nn = sizes[i].n;

        // fewer runs for large matrices
        int runs;
        if (m * nn <= 64 * 64) runs = 1000;
        else if (m * nn <= 256 * 256) runs = 50;
        else if (m * nn <= 512 * 512) runs = 5;
        else runs = 1;

        double avg = benchmark(m, k, nn, runs);

        // each result cell = k multiplies + (k-1) adds around 2k flops
        double flops = 2.0 * m * k * nn;
        double mflops = (flops / avg) / 1e6;

        char label[64];
        sprintf(label, "%dx%d * %dx%d", m, k, k, nn);
        printf("%-22s %8d %10.6f s %12.1f\n", label, runs, avg, mflops);
    }

    printf("\n");
    return 0;
}