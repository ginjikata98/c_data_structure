#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {
//  sArray *a = fArrayUniform(3, mArr(u32,2, 2, 2));
  sArray *a = fArrayNormal(3, mArr(u32, 2, 2, 2));
//  sArray *a = fArrayArrange(0, 12, 0.6);
  fArrayPrint(a);
//  fArrayReshape(a, 2, mArr(u32,1, 8));
//  fArrayPrint(a);


//  sArray *a = fArrayOnes(3, mArr(u32,2, 2, 2));


  return 0;
}