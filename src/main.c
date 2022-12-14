#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"

typedef struct {
  VmU32 kArm;
  VmF32 epsilon;
} Bandit;


int main(void) {
  srand(time(null));

  VmU32 dim[] = {2, 2, 2};
  VmNDArray *a = vmNDArrayOnes(3, dim);

  VmU32 access[] = {0, 1, 1};
  printf("%f", vmNDArrayGet(a, access));

  vmNDArrayPrint(a);


  return 0;
}