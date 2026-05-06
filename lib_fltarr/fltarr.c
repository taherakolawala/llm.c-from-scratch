#include "fltarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init(FloatArray* arr, int capacity){
    float* ptr = (float*)calloc(capacity, sizeof(float));
    if (ptr == NULL) {
        printf("Memory allocation failed");
        return;
    }
    arr->data = ptr;
    arr->capacity = capacity;
    arr->length = 0;
    return;
}

void push(FloatArray* arr, float value){
    if (arr->length >= arr->capacity){
        float* ptr = realloc(arr->data, (arr->capacity+10) * sizeof(float));
        if (ptr == NULL) {
            printf("Memory reallocation failed");
            return;
        }
        arr-> data = ptr;
        arr->capacity+= 10;
    }
   arr->data[arr->length] = value;
   arr->length++;
   return;
}

float get(FloatArray* arr, int index){
    if (arr->length <= index){
        printf("Invalid index.");
        return NAN;
    }
    return arr->data[index];
}

void freeArr(FloatArray* arr){
    free(arr->data);
    return;
}

void print(FloatArray* arr){
    printf("Data Pointer: %p, Length: %d, Capacity: %d\n", arr->data, arr->length, arr->capacity);
    printf("Values: ");
    for (int i = 0; i < arr->length; i++) {
        printf("%f\n", arr->data[i]);
    }
    return;
}
