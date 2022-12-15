#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct VmNDArray VmNDArray;

VmNDArray *vmNDArrayNew(f64 *data, u32 nd, u32 *dimensions);
VmNDArray *vmNDArrayOnes(u32 nd, u32 *dimensions);
void vmNDArrayPrint(VmNDArray *arr);
f64 vmNDArrayGet(VmNDArray *arr, u32 *ind);


#endif //MAIN_NDARRAY_H
