#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include "macro.h"

#define VMVec(T, name) typedef struct STRUCT_NAME(name) STRUCT_NAME(name); \
STRUCT_NAME(name) *VMPaste(FN_NAME(name), New) (VmU32 cap);\
void VMPaste(FN_NAME(name), Free) (STRUCT_NAME(name) *v);\
T *VMPaste(FN_NAME(name), At) (STRUCT_NAME(name) *v, VmU32 i);\

#define VMVecDef(T, name) struct VMPaste(Vm, name) { VmU32 size; VmU32 capacity; T *items;  }; \
STRUCT_NAME(name) *VMPaste(FN_NAME(name), New) (VmU32 cap) {\
STRUCT_NAME(name) *a = VMMalloc(a, sizeof(STRUCT_NAME(name)));\
a->capacity = cap > 0 ? cap : 16;\
a->size = 0;\
a->items = VMCalloc(a->items, a->capacity, sizeof(STRUCT_NAME(name)));\
return a;\
}                                                                                              \
void VMPaste(FN_NAME(name), Free) (STRUCT_NAME(name) *v) {                                                         \
VMFree(v->items);\
VMFree(v);\
}                                                                                              \
T *VMPaste(FN_NAME(name), At) (STRUCT_NAME(name) *v, VmU32 i) {                                 \
assert(i >= 0 && i < v->size);                                                                                               \
return &(v->items[i])       ;                                                                                        \
}



#define VMVecAdd(v, e) \
if ((v)->size == (v)->capacity) { \
  (v)->items = realloc((v)->items, (v)->capacity * 2 * sizeof((v)->items[0])); \
  VMAssert((v)->items != null);\
  (v)->capacity *= 2; \
}                      \
(v)->items[(v)->size++] = e

#define VMVecAt(v, i) (v)->items[(i)]

#define VMVecSort(v, cmp) (qsort((v)->items, (v)->size, sizeof(*(v)->items), cmp))

#define VMVecPop(v) VMAssert((v)->size > 0); (v)->size--

#define VMVecDelAt(v, i) VMAssert(i >= 0 && i < (v)->capacity); (v)->items[i] = (v)->items[--(v)->size]

VMVec(VmU32, VecU32);
VMVec(VmU64, VecU64);
VMVec(VmI64, VecI64);
VMVec(VmI32, VecI32);
VMVec(VmF32, VecF32);
VMVec(VmF64, VecF64);
VMVec(VmString, VecString);

#endif //C_DATA_STRUCTURE_LIBS_H
