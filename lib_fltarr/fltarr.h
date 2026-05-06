#ifndef FLTARR_H
#define FLTARR_H

typedef struct {
    float *data;
    int length;
    int capacity;
} FloatArray;


void init(FloatArray* arr, int capacity);
void push(FloatArray* arr, float value);
float get(FloatArray* arr, int index);
void freeArr(FloatArray* arr);
void print(FloatArray* arr);


#endif