#include <stdio.h>
#include <math.h>
#include "lib_matrix/matrix.h"
#include "RMS.h"  // or wherever your RMS function lives

int main() {
    // Test 1: simple known values [2, 4, 6, 8]
    // RMS = sqrt((4 + 16 + 36 + 64) / 4) = sqrt(30) ≈ 5.4772
    Matrix v1;
    mat_alloc(&v1, 1, 4);
    mat_set(&v1, 0, 0, 2.0f);
    mat_set(&v1, 0, 1, 4.0f);
    mat_set(&v1, 0, 2, 6.0f);
    mat_set(&v1, 0, 3, 8.0f);

    float result = RMS(&v1);
    printf("Test 1: RMS([2,4,6,8]) = %.4f (expected 5.4772)\n", result);

    // Test 2: all ones [1, 1, 1] -> RMS should be 1.0
    Matrix v2;
    mat_alloc(&v2, 1, 3);
    mat_set(&v2, 0, 0, 1.0f);
    mat_set(&v2, 0, 1, 1.0f);
    mat_set(&v2, 0, 2, 1.0f);

    result = RMS(&v2);
    printf("Test 2: RMS([1,1,1]) = %.4f (expected 1.0000)\n", result);

    // Test 3: single element [5] -> RMS should be 5.0
    Matrix v3;
    mat_alloc(&v3, 1, 1);
    mat_set(&v3, 0, 0, 5.0f);

    result = RMS(&v3);
    printf("Test 3: RMS([5]) = %.4f (expected 5.0000)\n", result);

    // Test 4: column vector should also work
    Matrix v4;
    mat_alloc(&v4, 3, 1);
    mat_set(&v4, 0, 0, 3.0f);
    mat_set(&v4, 1, 0, 4.0f);
    mat_set(&v4, 2, 0, 0.0f);

    result = RMS(&v4);
    // RMS = sqrt((9 + 16 + 0) / 3) = sqrt(25/3) ≈ 2.8868
    printf("Test 4: RMS([3,4,0] col) = %.4f (expected 2.8868)\n", result);

    // Test 5: 2D matrix should be rejected
    Matrix v5;
    mat_alloc(&v5, 2, 3);

    result = RMS(&v5);
    printf("Test 5: RMS(2x3 matrix) = %.4f (expected NaN)\n", result);

    mat_free(&v1);
    mat_free(&v2);
    mat_free(&v3);
    mat_free(&v4);
    mat_free(&v5);

    return 0;
}