#include <stdio.h>
#include <math.h>
#include "../lib_matrix/matrix.h"
#include "math_ops.h"

int main() {
    // ===== RMS TESTS =====

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
    printf("Test 4: RMS([3,4,0] col) = %.4f (expected 2.8868)\n", result);

    // Test 5: 2D matrix should be rejected
    Matrix v5;
    mat_alloc(&v5, 2, 3);
    result = RMS(&v5);
    printf("Test 5: RMS(2x3 matrix) = %.4f (expected NaN)\n", result);

    printf("\n");

    // ===== SOFTMAX TESTS =====

    // Test 6: softmax([2, 4, 6]) -> [0.0159, 0.1173, 0.8668]
    Matrix s1, s1_out;
    mat_alloc(&s1, 1, 3);
    mat_set(&s1, 0, 0, 2.0f);
    mat_set(&s1, 0, 1, 4.0f);
    mat_set(&s1, 0, 2, 6.0f);
    softmax(&s1, &s1_out);
    printf("Test 6: softmax([2,4,6]) = [%.4f, %.4f, %.4f] (expected [0.0159, 0.1173, 0.8668])\n",
           s1_out.data[0], s1_out.data[1], s1_out.data[2]);

    // Test 7: all same values -> should be uniform [0.3333, 0.3333, 0.3333]
    Matrix s2, s2_out;
    mat_alloc(&s2, 1, 3);
    mat_set(&s2, 0, 0, 5.0f);
    mat_set(&s2, 0, 1, 5.0f);
    mat_set(&s2, 0, 2, 5.0f);
    softmax(&s2, &s2_out);
    printf("Test 7: softmax([5,5,5]) = [%.4f, %.4f, %.4f] (expected [0.3333, 0.3333, 0.3333])\n",
           s2_out.data[0], s2_out.data[1], s2_out.data[2]);

    // Test 8: large values shouldn't overflow [90, 92, 94]
    Matrix s3, s3_out;
    mat_alloc(&s3, 1, 3);
    mat_set(&s3, 0, 0, 90.0f);
    mat_set(&s3, 0, 1, 92.0f);
    mat_set(&s3, 0, 2, 94.0f);
    softmax(&s3, &s3_out);
    printf("Test 8: softmax([90,92,94]) = [%.4f, %.4f, %.4f] (expected [0.0159, 0.1173, 0.8668])\n",
           s3_out.data[0], s3_out.data[1], s3_out.data[2]);

    // Test 9: outputs should sum to 1.0
    float sum = s3_out.data[0] + s3_out.data[1] + s3_out.data[2];
    printf("Test 9: sum of softmax([90,92,94]) = %.4f (expected 1.0000)\n", sum);

    // Test 10: single element -> should be 1.0
    Matrix s4, s4_out;
    mat_alloc(&s4, 1, 1);
    mat_set(&s4, 0, 0, 42.0f);
    softmax(&s4, &s4_out);
    printf("Test 10: softmax([42]) = [%.4f] (expected [1.0000])\n", s4_out.data[0]);

    // Test 11: 2D matrix should be rejected
    Matrix s5, s5_out;
    mat_alloc(&s5, 2, 3);
    softmax(&s5, &s5_out);
    printf("Test 11: softmax(2x3 matrix) rejected above\n");

    mat_free(&v1);
    mat_free(&v2);
    mat_free(&v3);
    mat_free(&v4);
    mat_free(&v5);
    mat_free(&s1); mat_free(&s1_out);
    mat_free(&s2); mat_free(&s2_out);
    mat_free(&s3); mat_free(&s3_out);
    mat_free(&s4); mat_free(&s4_out);
    mat_free(&s5);

    return 0;
}