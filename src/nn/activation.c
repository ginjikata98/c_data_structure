//
// Created by DUNG.VM on 26/12/2022.
//

#include "activation.h"

f32 fModuleActivationRelu(f32 x) {
  return x * (x > 0);
}

f32 activate(f32 x, ai_module_activation a) {
  switch (a) {
    case ai_module_activation_relu:
      return fModuleActivationRelu(x);
    case ai_module_activation_sigmoid:
      break;
    case ai_module_activation_tanh:
      break;
    case ai_module_activation_maxsize:
      break;
    default:
      return 0;
  }
  return 0;
}

void activate_array(f32* x, const i32 n, const ai_module_activation a) {
  int i;
  for (i = 0; i < n; ++i) {
    x[i] = activate(x[i], a);
  }
}