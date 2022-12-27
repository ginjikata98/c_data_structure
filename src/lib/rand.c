#include "rand.h"

u32 ai_random_randint(u32 min, u32 max) {
  if (max < min) {
    u32 s = min;
    min = max;
    max = s;
  }
  u32 r = (arc4random() % (max - min + 1)) + min;
  return r;
}

f64 ai_random_normal() {
  static u32 haveSpare = 0;
  static f64 rand1, rand2;

  if (haveSpare) {
    haveSpare = 0;
    return sqrt(rand1) * sin(rand2);
  }

  haveSpare = 1;

  rand1 = arc4random() / ((f64) UINT32_MAX);
  if (rand1 < 1e-100) { rand1 = 1e-100; }
  rand1 = -2 * log(rand1);
  rand2 = (arc4random() / ((f64) UINT32_MAX)) * 3.141592654 * 2;

  return sqrt(rand1) * cos(rand2);
}

f64 ai_random_uniform() {
  return ((f64) arc4random_uniform(UINT32_MAX) / UINT32_MAX);
}