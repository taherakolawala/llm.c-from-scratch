#include <math.h>
#include <stdlib.h>
#include "../lib_matrix/matrix.h"
#include <stdio.h>
#include "math_ops.h"

float RMS(Matrix* m){
    if ( m-> cols != 1 && m->rows != 1){
        printf("Invalid matrix dimensions. Must be a vector.\n");
        return NAN;
    }
    int n = m->cols * m->rows;
    float sum = 0.0f; 
    for (int i = 0; i < n; i++){
        sum += m->data[i] * m->data[i];
    }
    float rms = sqrtf(sum / n);
    return rms;
}

void softmax(Matrix* m, Matrix* output){
    if (m->cols != 1 && m->rows != 1){
        printf("Invalid matrix dimensions. Must be a vector.\n");
        return;
    }
    mat_alloc(output, m->rows, m->cols);
    int n = m->cols * m->rows;

    float max = m->data[0];
    for (int i = 1; i < n; i++){
        if (m->data[i] > max) max = m->data[i];
    }

    float sum = 0.0f;
    for (int i = 0; i < n; i++){
        output->data[i] = expf(m->data[i] - max);
        sum += output->data[i];
    }
    for (int i = 0; i < n; i++){
        output->data[i] = output->data[i] / sum;
    }
}