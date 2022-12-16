#include "std.h"

mVecDef(u32, VecU32);
mVecDef(u64, VecU64);
mVecDef(i64, VecI64);
mVecDef(i32, VecI32);
mVecDef(f32, VecF32);
mVecDef(f64, VecF64);
mVecDef(string, VecString);



void *fMemClone(void *src, size s) {
  assert(src);
  void *p = mMalloc(p, s);
  memmove(p, src, s);
  return p;
}

void fMemCopy(void *src, void*dest, size s) {
  assert(src && dest);
  memmove(dest, src, s);
}
