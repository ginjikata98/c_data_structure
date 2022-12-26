//
// Created by DUNG.VM on 26/12/2022.
//



#ifndef MAIN_ACTIVATION_H
#define MAIN_ACTIVATION_H

#include "nn.h"


f32 fModuleActivationRelu(f32 x) {
  return x * (x > 0);
}

f32 activate(f32 x, eModuleActivation a) {
  switch (a) {
    case emModuleActivationRelu:
      return fModuleActivationRelu(x);
  }
}


void activate_array(f32 *x, const i32 n, const eModuleActivation a) {
  int i;
  for (i = 0; i < n; ++i) {
    x[i] = activate(x[i], a);
  }
}

#endif //MAIN_ACTIVATION_H
