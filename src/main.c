#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {
//  sArray *a = fArrayUniform(3, mShape(2, 2, 2));
  sArray *a = fArrayNormal(3, mShape(2, 2, 2));
  fArrayPrint(a);
  fArrayReshape(a, 2, mShape(1, 8));
  fArrayPrint(a);


//  sArray *a = fArrayOnes(3, mShape(2, 2, 2));


  return 0;
}