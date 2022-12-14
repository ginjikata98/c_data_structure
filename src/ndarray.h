#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "std.h"

typedef struct VmNDArray VmNDArray;

VmNDArray *vmNpInit(VmF32 *data, VmU32 nd, VmU32 *dimensions);
VmF32 *vmNpGet(VmNDArray *obj, VmU32 const *ind);


#endif //MAIN_NDARRAY_H
