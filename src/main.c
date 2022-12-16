#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {
  sArray *a = fArrayNormal(3, mArr(u32, 2, 2, 2));
  sArray *b = fArrayNormal(3, mArr(u32, 2, 2, 2));
  fArrayPrint(a);
  fArrayPrint(b);
//  sArray *c = fArrayZeros(3, mArr(u32, 2, 2, 2));

  fArrayPow(a, b, a);

  fArrayPrint(a);

//  sArray *a = fArrayOnes(3, mArr(u32,2, 2, 2));

  printf("%f", pow(-0.7253, 1.3724));

  return 0;
}