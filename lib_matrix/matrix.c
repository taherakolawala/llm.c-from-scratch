#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mat_alloc(Matrix *m, int rows, int cols){
    float* ptr = (float*)calloc(rows * cols, sizeof(float));
    if (ptr == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    m->data = ptr;
    m->rows = rows;
    m->cols = cols;
    printf("Matrix successfully allocated.\n");
    return;
}

float mat_get(Matrix* m, int rows, int cols){
    if (rows > m->rows || cols > m->cols){
        printf("Invalid index.\n");
        return NAN;
    }
    return m->data[rows*cols];
}

void mat_set(Matrix* m, int row, int col, float val){
    if (row > m->rows || col > m->cols){
        printf("Invalid index.\n");
        return;
    }
    m->data[row*col] = val;
    return; 
}

void mat_mul(Matrix* a, Matrix* b, Matrix* output){
    if (a->cols != b->rows){
        printf("Invalid matrix dimensions.\n");
        return;
    }
    mat_alloc(output, a->rows, b->cols);
    
}

void mat_free(Matrix *m){
    free(m->data);
    return;
}
