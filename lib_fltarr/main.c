//test file for dynamic float array library

#include <stdio.h>
#include "fltarr.h"

int main() {
    FloatArray arr;

    init(&arr, 2);
    push(&arr, 3.14f);
    push(&arr, 2.71f);
    printf("DEBUG:\n");
    print(&arr);
    push(&arr, 0.01f);
    printf("DEBUG:\n");
    print(&arr);
    float x = get(&arr, 0);
    printf("\nIndex 0: %f\n", x);
    float y = get(&arr, 2);
    printf("Index 2: %f\n", y);
    float invalid = get(&arr, 20);
    printf("Index 20 (Invalid): %f\n", invalid);
    freeArr(&arr);

    return 0;
}