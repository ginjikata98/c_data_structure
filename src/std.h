#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include "macro.h"

#define mVec(T, name) typedef struct mStructName(name) mStructName(name); \
mStructName(name) *mPaste(mFnName(name), New) (u32 cap);\
void mPaste(mFnName(name), Free) (mStructName(name) *v);\
T *mPaste(mFnName(name), At) (mStructName(name) *v, u32 i);\
void mPaste(mFnName(name), DelAt) (mStructName(name) *v, u32 i);\
void mPaste(mFnName(name), Sort) (mStructName(name) *v);\
T *mPaste(mFnName(name), Pop) (mStructName(name) *v);\
void mPaste(mFnName(name), Push) (mStructName(name) *v, T t);\
u32 mPaste(mFnName(name), Size) (mStructName(name) *v);\
bool mPaste(mFnName(name), IsEmpty) (mStructName(name) *v);\

#define mVecDef(T, name) struct mStructName(name) { u32 size; u32 capacity; T *items;  }; \
mStructName(name) *mPaste(mFnName(name), New) (u32 cap) {\
mStructName(name) *a = mMalloc(a, sizeof(mStructName(name)));\
a->capacity = cap > 0 ? cap : 16;\
a->size = 0;\
a->items = mCalloc(a->items, a->capacity, sizeof(T));\
return a;\
}                                                                                              \
void mPaste(mFnName(name), Free) (mStructName(name) *v) {                                                         \
mFree(v->items);\
mFree(v);\
}                                                                                              \
T *mPaste(mFnName(name), At) (mStructName(name) *v, u32 i) {                                 \
assert(i >= 0 && i < v->size);                                                                                               \
return &(v->items[i])       ;                                                                                        \
}\
void mPaste(mFnName(name), DelAt) (mStructName(name) *v, u32 i) {                           \
assert(i >= 0 && i < v->size); v->items[i] = v->items[--v->size];                                                                                               \
}                                                                                              \
T *mPaste(mFnName(name), Pop) (mStructName(name) *v) {                                        \
return &(v->items[--v->size]);                                                                                               \
}                                                                                              \
void mPaste(mFnName(name), Sort) (mStructName(name) *v){                                      \
qsort(v->items, v->size, sizeof(v->items), null);                                                                                               \
}                                                                                              \
void mPaste(mFnName(name), Push) (mStructName(name) *v, T t){                                 \
if (v->size == v->capacity) { \
  v->items = mRealloc(v->items, v->capacity * 2 * sizeof(T)); \
  v->capacity *= 2; \
}                      \
v->items[v->size++] = t;                                                                                               \
}                                                                                              \
u32 mPaste(mFnName(name), Size) (mStructName(name) *v){                                     \
return v->size;                                                                                               \
}                                                                                              \
bool mPaste(mFnName(name), IsEmpty) (mStructName(name) *v) {                                \
return v->size == 0;                                                                                               \
}

mVec(u32, VecU32);
mVec(u64, VecU64);
mVec(i64, VecI64);
mVec(i32, VecI32);
mVec(f32, VecF32);
mVec(f64, VecF64);
mVec(string, VecString);

#endif //C_DATA_STRUCTURE_LIBS_H
