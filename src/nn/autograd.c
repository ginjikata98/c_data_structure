//
// Created by Tony Vu on 28/12/2022.
//

#include "autograd.h"
#include "../lib/sds.h"

void dummy_(ai_value *v) {

}

void ai_value_add_deriv(ai_value *self);
void ai_value_mul_deriv(ai_value *self);
void ai_value_sub_deriv(ai_value *self);
void ai_value_div_deriv(ai_value *self);
void ai_value_pow_deriv(ai_value *self);
void ai_value_neg_deriv(ai_value *self);
void ai_value_relu_deriv(ai_value *self);

static u64 ai_value_gen_id() {
  static u64 id = 0;
  return id++;
}

ai_value *ai_value_new(f32 data) {
  ai_value *v = ai_m_calloc(v, 1, sizeof(ai_value));
  v->id = ai_value_gen_id();
  v->data = data;
  v->grad = 0;
  v->backward = dummy_;
  v->children = ai_m_calloc(v->children, 2, sizeof(ai_value));
  return v;
}

ai_value *ai_value_add(ai_value *self, ai_value *other) {
  assert(self && other);
  ai_value *out = ai_value_new(self->data + other->data);
  out->children[0] = self;
  out->children[1] = other;
  out->backward = ai_value_add_deriv;
  return out;
}

void ai_value_add_deriv(ai_value *self) {
  assert(self && self->children[0] && self->children[1]);
  self->children[0]->grad += self->grad;
  self->children[1]->grad += self->grad;
}

ai_value *ai_value_mul(ai_value *self, ai_value *other) {
  assert(self && other);
  ai_value *out = ai_value_new(self->data * other->data);
  out->children[0] = self;
  out->children[1] = other;
  out->backward = ai_value_mul_deriv;
  return out;
}

void ai_value_mul_deriv(ai_value *self) {
  assert(self && self->children[0] && self->children[1]);
  self->children[0]->grad += self->grad * self->children[1]->data;
  self->children[1]->grad += self->grad * self->children[0]->data;
}

ai_value *ai_value_sub(ai_value *self, ai_value *other);
ai_value *ai_value_div(ai_value *self, ai_value *other);
ai_value *ai_value_pow(ai_value *self, f32 other);
ai_value *ai_value_neg(ai_value *self);
ai_value *ai_value_relu(ai_value *self);

void ai_value_backward(ai_value *self);

string ai_value_str(ai_value *self) {
  string s = sdsempty();
  s = sdscatprintf(s, "Value(id=%llu, data=%.4f, grad=%.4f)", self->id, self->data, self->grad);
  return s;
}
