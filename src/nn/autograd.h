//
// Created by Tony Vu on 28/12/2022.
//

#ifndef MAIN_SRC_NN_AUTOGRAD_H_
#define MAIN_SRC_NN_AUTOGRAD_H_

#include "../core/types.h"
struct ai_value;
typedef struct ai_value ai_value;

struct ai_value {
  u64 id;
  f32 data;
  f32 grad;
  ai_value *children;
  void (*backward)(ai_value *self);
};

ai_value *ai_value_new(f32 data);
ai_value *ai_value_add(ai_value *self, ai_value *other);
ai_value *ai_value_mul(ai_value *self, ai_value *other);
ai_value *ai_value_sub(ai_value *self, ai_value *other);
ai_value *ai_value_div(ai_value *self, ai_value *other);
ai_value *ai_value_pow(ai_value *self, f32 other);
ai_value *ai_value_neg(ai_value *self);
ai_value *ai_value_relu(ai_value *self);

void ai_value_backward(ai_value *self);
string ai_value_str(ai_value *self);

#endif //MAIN_SRC_NN_AUTOGRAD_H_
