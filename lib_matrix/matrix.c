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
    return;
}

float mat_get(Matrix* m, int rows, int cols){
    if (rows > m->rows || cols > m->cols){
        printf("Invalid index.\n");
        return NAN;
    }
    return m->data[rows*(m->cols) + cols];
}

void mat_set(Matrix* m, int row, int col, float val){
    if (row > m->rows || col > m->cols){
        printf("Invalid index.\n");
        return;
    }
    m->data[row*(m->cols) + col] = val;
    return; 
}

void mat_mul(Matrix* a, Matrix* b, Matrix* output){
    if (output == a || output == b) {
        printf("Output must not alias input.\n");
        return;
    }
    if (a->cols != b->rows){
        printf("Invalid matrix dimensions.\n");
        return;
    }
    mat_alloc(output, a->rows, b->cols);
    for (int i = 0; i < a->rows; i++){
        for (int j = 0; j < b->cols; j++){
            float value = 0;
            for (int k=0; k< a->cols; k++){
                value += (a->data[i*(a->cols) + k]) * (b->data[k*(b->cols) + j]);
            }
            output->data[i*(output->cols) + j] = value;
        }
    }
    return;
}

void mat_print(Matrix *m){
    if (m == NULL){
        printf("Invalid matrix pointer \n");
        return;
    }
    printf("Rows: %d, Columns: %d\n\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->cols; j++){
            printf("%f ", m->data[i*(m->cols) + j]);
        }
        printf("\n");
    }
    return;
}

void mat_free(Matrix *m){
    free(m->data);
    return;
}
