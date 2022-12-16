#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {
  sTensor *a = fTensorNormal(3, mArr(u32, 2, 2, 2));
  sTensor *b = fTensorNormal(3, mArr(u32, 2, 2, 2));
  sTensor *c = fTensorClone(a);
  fTensorPrint(a);
  fTensorPrint(c);

  printf("\n\n");

  fTensorSub(a, b, a);
  fTensorPrint(a);
  fTensorPrint(c);

  return 0;
}