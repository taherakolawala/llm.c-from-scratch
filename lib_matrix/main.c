#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

#define EPSILON 1e-6
#define ASSERT_FLOAT(a, b) assert(fabs((a) - (b)) < EPSILON)

static int tests_passed = 0;
static int tests_total = 0;

#define RUN_TEST(fn) do { \
    tests_total++; \
    printf("  %-40s", #fn); \
    fn(); \
    tests_passed++; \
    printf("passed\n"); \
} while(0)

/* ── mat_alloc ─────────────────────────────────────── */

void test_alloc_basic() {
    Matrix m;
    mat_alloc(&m, 3, 4);
    assert(m.rows == 3);
    assert(m.cols == 4);
    assert(m.data != NULL);
    mat_free(&m);
}

void test_alloc_single_element() {
    Matrix m;
    mat_alloc(&m, 1, 1);
    assert(m.rows == 1);
    assert(m.cols == 1);
    assert(m.data != NULL);
    mat_free(&m);
}

void test_alloc_large() {
    Matrix m;
    mat_alloc(&m, 100, 200);
    assert(m.rows == 100);
    assert(m.cols == 200);
    assert(m.data != NULL);
    mat_free(&m);
}

/* ── mat_set / mat_get ─────────────────────────────── */

void test_set_get_basic() {
    Matrix m;
    mat_alloc(&m, 3, 3);
    mat_set(&m, 0, 0, 1.0f);
    mat_set(&m, 1, 2, 5.5f);
    mat_set(&m, 2, 1, -3.0f);
    ASSERT_FLOAT(mat_get(&m, 0, 0), 1.0f);
    ASSERT_FLOAT(mat_get(&m, 1, 2), 5.5f);
    ASSERT_FLOAT(mat_get(&m, 2, 1), -3.0f);
    mat_free(&m);
}

void test_set_get_all_elements() {
    Matrix m;
    mat_alloc(&m, 4, 5);
    float val = 0.0f;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            mat_set(&m, i, j, val);
            val += 1.0f;
        }
    }
    val = 0.0f;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            ASSERT_FLOAT(mat_get(&m, i, j), val);
            val += 1.0f;
        }
    }
    mat_free(&m);
}

void test_set_overwrite() {
    Matrix m;
    mat_alloc(&m, 2, 2);
    mat_set(&m, 0, 0, 10.0f);
    mat_set(&m, 0, 0, 99.0f);
    ASSERT_FLOAT(mat_get(&m, 0, 0), 99.0f);
    mat_free(&m);
}

void test_set_get_negative_values() {
    Matrix m;
    mat_alloc(&m, 2, 2);
    mat_set(&m, 0, 0, -42.5f);
    mat_set(&m, 1, 1, -0.001f);
    ASSERT_FLOAT(mat_get(&m, 0, 0), -42.5f);
    ASSERT_FLOAT(mat_get(&m, 1, 1), -0.001f);
    mat_free(&m);
}

/* ── mat_mul ───────────────────────────────────────── */

void test_mul_2x3_times_3x2() {
    Matrix a, b, r;
    mat_alloc(&a, 2, 3);
    mat_alloc(&b, 3, 2);

    float ad[] = {1, 2, 3, 4, 5, 6};
    float bd[] = {7, 8, 9, 10, 11, 12};
    for (int i = 0; i < 6; i++) { a.data[i] = ad[i]; b.data[i] = bd[i]; }

    mat_mul(&a, &b, &r);

    assert(r.rows == 2);
    assert(r.cols == 2);
    ASSERT_FLOAT(mat_get(&r, 0, 0), 58.0f);
    ASSERT_FLOAT(mat_get(&r, 0, 1), 64.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 0), 139.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 1), 154.0f);

    mat_free(&a); mat_free(&b); mat_free(&r);
}

void test_mul_2x3_times_3x4() {
    Matrix a, b, r;
    mat_alloc(&a, 2, 3);
    mat_alloc(&b, 3, 4);

    float ad[] = {2, 0, 1, 3, 1, 2};
    float bd[] = {1, 4, 0, 2, 3, 1, 2, 0, 5, 2, 1, 3};
    for (int i = 0; i < 6; i++) a.data[i] = ad[i];
    for (int i = 0; i < 12; i++) b.data[i] = bd[i];

    mat_mul(&a, &b, &r);

    assert(r.rows == 2);
    assert(r.cols == 4);
    ASSERT_FLOAT(mat_get(&r, 0, 0), 7.0f);
    ASSERT_FLOAT(mat_get(&r, 0, 1), 10.0f);
    ASSERT_FLOAT(mat_get(&r, 0, 2), 1.0f);
    ASSERT_FLOAT(mat_get(&r, 0, 3), 7.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 0), 16.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 1), 17.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 2), 4.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 3), 12.0f);

    mat_free(&a); mat_free(&b); mat_free(&r);
}

void test_mul_identity() {
    Matrix a, id, r;
    mat_alloc(&a, 3, 3);
    mat_alloc(&id, 3, 3);

    float ad[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    float idd[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    for (int i = 0; i < 9; i++) { a.data[i] = ad[i]; id.data[i] = idd[i]; }

    mat_mul(&a, &id, &r);

    for (int i = 0; i < 9; i++) {
        ASSERT_FLOAT(r.data[i], ad[i]);
    }

    mat_free(&a); mat_free(&id); mat_free(&r);
}

void test_mul_1x1() {
    Matrix a, b, r;
    mat_alloc(&a, 1, 1);
    mat_alloc(&b, 1, 1);
    a.data[0] = 3.0f;
    b.data[0] = 7.0f;

    mat_mul(&a, &b, &r);

    assert(r.rows == 1);
    assert(r.cols == 1);
    ASSERT_FLOAT(r.data[0], 21.0f);

    mat_free(&a); mat_free(&b); mat_free(&r);
}

void test_mul_zeros() {
    Matrix a, b, r;
    mat_alloc(&a, 2, 3);
    mat_alloc(&b, 3, 2);
    for (int i = 0; i < 6; i++) { a.data[i] = 0.0f; b.data[i] = 0.0f; }

    mat_mul(&a, &b, &r);

    for (int i = 0; i < 4; i++) {
        ASSERT_FLOAT(r.data[i], 0.0f);
    }

    mat_free(&a); mat_free(&b); mat_free(&r);
}

void test_mul_column_times_row() {
    Matrix a, b, r;
    mat_alloc(&a, 3, 1);
    mat_alloc(&b, 1, 3);
    a.data[0] = 2; a.data[1] = 3; a.data[2] = 4;
    b.data[0] = 5; b.data[1] = 6; b.data[2] = 7;

    mat_mul(&a, &b, &r);

    assert(r.rows == 3);
    assert(r.cols == 3);
    ASSERT_FLOAT(mat_get(&r, 0, 0), 10.0f);
    ASSERT_FLOAT(mat_get(&r, 0, 2), 14.0f);
    ASSERT_FLOAT(mat_get(&r, 1, 1), 18.0f);
    ASSERT_FLOAT(mat_get(&r, 2, 0), 20.0f);
    ASSERT_FLOAT(mat_get(&r, 2, 2), 28.0f);

    mat_free(&a); mat_free(&b); mat_free(&r);
}

void test_mul_row_times_column() {
    Matrix a, b, r;
    mat_alloc(&a, 1, 3);
    mat_alloc(&b, 3, 1);
    a.data[0] = 2; a.data[1] = 3; a.data[2] = 4;
    b.data[0] = 5; b.data[1] = 6; b.data[2] = 7;

    mat_mul(&a, &b, &r);

    assert(r.rows == 1);
    assert(r.cols == 1);
    ASSERT_FLOAT(r.data[0], 56.0f);  // 10 + 18 + 28

    mat_free(&a); mat_free(&b); mat_free(&r);
}

/* ── mat_transpose ─────────────────────────────────── */

void test_transpose_2x3() {
    Matrix a, t;
    mat_alloc(&a, 2, 3);
    float ad[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) a.data[i] = ad[i];

    mat_transpose(&a, &t);

    assert(t.rows == 3);
    assert(t.cols == 2);
    // [1 2 3]T = [1 4]
    // [4 5 6]    [2 5]
    //            [3 6]
    ASSERT_FLOAT(mat_get(&t, 0, 0), 1.0f);
    ASSERT_FLOAT(mat_get(&t, 0, 1), 4.0f);
    ASSERT_FLOAT(mat_get(&t, 1, 0), 2.0f);
    ASSERT_FLOAT(mat_get(&t, 1, 1), 5.0f);
    ASSERT_FLOAT(mat_get(&t, 2, 0), 3.0f);
    ASSERT_FLOAT(mat_get(&t, 2, 1), 6.0f);

    mat_free(&a); mat_free(&t);
}

void test_transpose_square() {
    Matrix a, t;
    mat_alloc(&a, 3, 3);
    float ad[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++) a.data[i] = ad[i];

    mat_transpose(&a, &t);

    assert(t.rows == 3);
    assert(t.cols == 3);
    ASSERT_FLOAT(mat_get(&t, 0, 0), 1.0f);
    ASSERT_FLOAT(mat_get(&t, 0, 1), 4.0f);
    ASSERT_FLOAT(mat_get(&t, 0, 2), 7.0f);
    ASSERT_FLOAT(mat_get(&t, 1, 0), 2.0f);
    ASSERT_FLOAT(mat_get(&t, 1, 1), 5.0f);
    ASSERT_FLOAT(mat_get(&t, 1, 2), 8.0f);
    ASSERT_FLOAT(mat_get(&t, 2, 0), 3.0f);
    ASSERT_FLOAT(mat_get(&t, 2, 1), 6.0f);
    ASSERT_FLOAT(mat_get(&t, 2, 2), 9.0f);

    mat_free(&a); mat_free(&t);
}

void test_transpose_1x1() {
    Matrix a, t;
    mat_alloc(&a, 1, 1);
    a.data[0] = 42.0f;

    mat_transpose(&a, &t);

    assert(t.rows == 1);
    assert(t.cols == 1);
    ASSERT_FLOAT(t.data[0], 42.0f);

    mat_free(&a); mat_free(&t);
}

void test_transpose_column_vector() {
    Matrix a, t;
    mat_alloc(&a, 4, 1);
    a.data[0] = 1; a.data[1] = 2; a.data[2] = 3; a.data[3] = 4;

    mat_transpose(&a, &t);

    assert(t.rows == 1);
    assert(t.cols == 4);
    ASSERT_FLOAT(t.data[0], 1.0f);
    ASSERT_FLOAT(t.data[1], 2.0f);
    ASSERT_FLOAT(t.data[2], 3.0f);
    ASSERT_FLOAT(t.data[3], 4.0f);

    mat_free(&a); mat_free(&t);
}

void test_transpose_row_vector() {
    Matrix a, t;
    mat_alloc(&a, 1, 4);
    a.data[0] = 5; a.data[1] = 6; a.data[2] = 7; a.data[3] = 8;

    mat_transpose(&a, &t);

    assert(t.rows == 4);
    assert(t.cols == 1);
    ASSERT_FLOAT(t.data[0], 5.0f);
    ASSERT_FLOAT(t.data[1], 6.0f);
    ASSERT_FLOAT(t.data[2], 7.0f);
    ASSERT_FLOAT(t.data[3], 8.0f);

    mat_free(&a); mat_free(&t);
}

void test_transpose_double_is_original() {
    Matrix a, t1, t2;
    mat_alloc(&a, 2, 4);
    float ad[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 8; i++) a.data[i] = ad[i];

    mat_transpose(&a, &t1);
    mat_transpose(&t1, &t2);

    // (A^T)^T == A
    assert(t2.rows == 2);
    assert(t2.cols == 4);
    for (int i = 0; i < 8; i++) {
        ASSERT_FLOAT(t2.data[i], ad[i]);
    }

    mat_free(&a); mat_free(&t1); mat_free(&t2);
}

/* ── mat_print (smoke test, just make sure it doesn't crash) ── */

void test_print_doesnt_crash() {
    Matrix m;
    mat_alloc(&m, 2, 3);
    for (int i = 0; i < 6; i++) m.data[i] = (float)i;
    printf("\n    [print output] ");
    mat_print(&m);
    printf("    ");
    mat_free(&m);
}

void test_print_null() {
    printf("\n    [expected error] ");
    mat_print(NULL);
    printf("    ");
}

/* ── main ──────────────────────────────────────────── */

int main() {
    printf("\n=== matrix library tests ===\n\n");

    printf("mat_alloc:\n");
    RUN_TEST(test_alloc_basic);
    RUN_TEST(test_alloc_single_element);
    RUN_TEST(test_alloc_large);

    printf("\nmat_set / mat_get:\n");
    RUN_TEST(test_set_get_basic);
    RUN_TEST(test_set_get_all_elements);
    RUN_TEST(test_set_overwrite);
    RUN_TEST(test_set_get_negative_values);

    printf("\nmat_mul:\n");
    RUN_TEST(test_mul_2x3_times_3x2);
    RUN_TEST(test_mul_2x3_times_3x4);
    RUN_TEST(test_mul_identity);
    RUN_TEST(test_mul_1x1);
    RUN_TEST(test_mul_zeros);
    RUN_TEST(test_mul_column_times_row);
    RUN_TEST(test_mul_row_times_column);

    printf("\nmat_transpose:\n");
    RUN_TEST(test_transpose_2x3);
    RUN_TEST(test_transpose_square);
    RUN_TEST(test_transpose_1x1);
    RUN_TEST(test_transpose_column_vector);
    RUN_TEST(test_transpose_row_vector);
    RUN_TEST(test_transpose_double_is_original);

    printf("\nmat_print:\n");
    RUN_TEST(test_print_doesnt_crash);
    RUN_TEST(test_print_null);

    printf("\n=== %d / %d tests passed ===\n\n", tests_passed, tests_total);
    return (tests_passed == tests_total) ? 0 : 1;
}