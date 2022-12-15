#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct sArray sArray;

#define mShape(...) (size[]) {__VA_ARGS__}

sArray *fArrayNew(f64 *data, size nd, size *dimensions);
sArray *fArrayOnes(size nd, size *dimensions);
sArray *fArrayZeros(size nd, size *dimensions);
sArray *fArrayArrange(i32 start, i32 end);
void *fArrayReshape(size nd, size *dimensions);
void fArrayPrint(sArray *arr);
f64 fArrayGet(sArray *arr, size *ind);


#endif //MAIN_NDARRAY_H
