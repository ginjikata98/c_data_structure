#ifndef MAIN_SRC_NN_AUTOGRAD_H_
#define MAIN_SRC_NN_AUTOGRAD_H_

#include "../core/types.h"

struct ai_value;
typedef struct ai_value ai_value;
struct ai_value_api;
typedef struct ai_value_api ai_value_api;

struct ai_value {
  u64 id;
  f32 data;
  f32 grad;
  ai_value **children;
  void (*backward)(ai_value *self);
};

struct ai_value_api {
  ai_value *(*from)(f32 data);
  ai_value *(*add)(ai_value *self, ai_value *other);
  ai_value *(*mul)(ai_value *self, ai_value *other);
  ai_value *(*sub)(ai_value *self, ai_value *other);
  ai_value *(*div)(ai_value *self, ai_value *other);
  ai_value *(*pow)(ai_value *self, f32 other);
  ai_value *(*neg)(ai_value *self);
  ai_value *(*relu)(ai_value *self);
  void (*backward)(ai_value *self);
  string (*str)(ai_value *self);
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

#define ai_m_import_value(alias) \
ai_value_api alias = {\
.from = ai_value_new,\
.add = ai_value_add,\
.mul = ai_value_mul,\
.sub = ai_value_sub,\
.div = ai_value_div,\
.pow = ai_value_pow,\
.neg = ai_value_neg,\
.relu = ai_value_relu,\
.backward = ai_value_backward,\
.str = ai_value_str,\
}\

#endif //MAIN_SRC_NN_AUTOGRAD_H_
