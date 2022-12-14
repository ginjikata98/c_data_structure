#include "rand.h"


VmU32 vmRandU32(VmU32 min, VmU32 max) {
  if (max < min) {
    VmU32 s = min;
    min = max;
    max = s;
  }
  VmU32 r = (rand() % (max - min + 1)) + min;
  return r;
}

// From http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
VmF32 vmRandNormal() {
  static VmU32 haveSpare = 0;
  static VmF64 rand1, rand2;

  if (haveSpare) {
    haveSpare = 0;
    return sqrt(rand1) * sin(rand2);
  }

  haveSpare = 1;

  rand1 = rand() / ((VmF64) RAND_MAX);
  if (rand1 < 1e-100) { rand1 = 1e-100; }
  rand1 = -2 * log(rand1);
  rand2 = (rand() / ((VmF64) RAND_MAX)) * VMPi * 2;

  return sqrt(rand1) * cos(rand2);
}

VmF32 vmRandUniform(VmF32 min, VmF32 max) {
  if (max < min) {
    VmF32 swap = min;
    min = max;
    max = swap;
  }
  return ((VmF32) rand() / RAND_MAX * (max - min)) + min;
}
