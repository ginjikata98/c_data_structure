#ifndef MAIN_NDARRAY_H
#define MAIN_NDARRAY_H

#include "macros.h"

typedef struct NDArray NDArray;

NDArray *NDArray_init(f32 *data, u32 nd, u32 *dimensions);
f32 *NDArray_get(NDArray *obj, u32 const *ind);


#endif //MAIN_NDARRAY_H
