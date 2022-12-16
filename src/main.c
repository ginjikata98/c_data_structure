#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {
  sArray *a = fArrayNormal(3, mArr(u32, 2, 2, 2));
  sArray *b = fArrayNormal(3, mArr(u32, 2, 2, 2));
  sArray *c = fArrayClone(a);
  fArrayPrint(a);
  fArrayPrint(c);

  printf("\n\n");

  fArraySub(a, b, a);
  fArrayPrint(a);
  fArrayPrint(c);

  return 0;
}