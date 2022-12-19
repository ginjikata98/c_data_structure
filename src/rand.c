#include "rand.h"

u32 fRandU32(u32 min, u32 max) {
  if (max < min) {
    u32 s = min;
    min = max;
    max = s;
  }
  u32 r = (arc4random() % (max - min + 1)) + min;
  return r;
}

f64 fRandNormal() {
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

f64 fRandUniform() {
  return ((f64) arc4random_uniform(UINT32_MAX) / UINT32_MAX);
}