#define DEBUG

#include "std.h"
#include "ndarray.h"

int main(void) {

  sArray *a = fArrayArrange(0, 12);
  fArrayPrint(a);
  fArrayReshape(a, 3, mShape(3, 2, 2));
  fArrayPrint(a);


//  sArray *a = fArrayOnes(3, mShape(2, 2, 2));


  return 0;
}