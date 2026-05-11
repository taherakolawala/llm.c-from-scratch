#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    float* data;
    int rows;
    int cols;
} Matrix;

void mat_alloc(Matrix *m, int rows, int cols);
void mat_free(Matrix *m);
float mat_get(Matrix* m, int rows, int cols);
void mat_set(Matrix* m, int row, int col, float val);
void mat_mul(Matrix* a, Matrix* b, Matrix* output);
void mat_print(Matrix *m);

#endif