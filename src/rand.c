#include "rand.h"


u32 vmRandU32(u32 min, u32 max) {
  if (max < min) {
    u32 s = min;
    min = max;
    max = s;
  }
  u32 r = (rand() % (max - min + 1)) + min;
  return r;
}

// From http://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
f32 vmRandNormal() {
  static u32 haveSpare = 0;
  static f64 rand1, rand2;

  if (haveSpare) {
    haveSpare = 0;
    return sqrt(rand1) * sin(rand2);
  }

  haveSpare = 1;

  rand1 = rand() / ((f64) RAND_MAX);
  if (rand1 < 1e-100) { rand1 = 1e-100; }
  rand1 = -2 * log(rand1);
  rand2 = (rand() / ((f64) RAND_MAX)) * mPi * 2;

  return sqrt(rand1) * cos(rand2);
}

f32 vmRandUniform(f32 min, f32 max) {
  if (max < min) {
    f32 swap = min;
    min = max;
    max = swap;
  }
  return ((f32) rand() / RAND_MAX * (max - min)) + min;
}
