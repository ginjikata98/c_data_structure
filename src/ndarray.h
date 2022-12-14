#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct VmNDArray VmNDArray;

VmNDArray *vmNDArrayNew(VmF64 *data, VmU32 nd, VmU32 *dimensions);
VmNDArray *vmNDArrayOnes(VmU32 nd, VmU32 *dimensions);
void vmNDArrayPrint(VmNDArray *arr);
VmF64 vmNDArrayGet(VmNDArray *arr, VmU32 *ind);


#endif //MAIN_NDARRAY_H
