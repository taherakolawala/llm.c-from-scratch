#include <math.h>
#include <stdlib.h>
#include "lib_matrix/matrix.h"
#include <stdio.h>
#include "RMS.h"

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
