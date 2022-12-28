#include "std.h"

void *fMemClone(void *src, size s) {
  assert(src);
  void *p = ai_m_malloc(p, s);
  memmove(p, src, s);
  return p;
}

void fMemCopy(void *src, void *dest, size s) {
  assert(src && dest);
  memmove(dest, src, s);
}

f64 track(void (*fn)(void)) {
  clock_t t;
  t = clock();
  fn();
  t = clock() - t;
  return ((f64) t) / CLOCKS_PER_SEC;
}
