//
// Created by DUNG.VM on 28/12/2022.
//

#include "vec.h"

struct ai_vec {
  i32 idx;
  i32 cap;
  size ele_size;
  byte buf[];
};


ai_vec *ai_vec_empty(i32 capacity, size element_size) {
  assert(capacity > 0);
  ai_vec *v = ai_m_malloc(v, sizeof(ai_vec) + capacity * element_size);
  v->cap = capacity * element_size;
  v->ele_size = element_size;
  return v;
}

void *ai_vec_get(ai_vec *v, i32 idx) {
  assert(v && idx >= 0 && v->idx >= v->ele_size * idx);
  return (void *) (v->buf + idx * v->ele_size);
}

void ai_vec_push(ai_vec *v, byte *value) {
  assert(v && value);
  memcpy(v->buf + v->idx, value, v->ele_size);
  v->idx += v->ele_size;
}

void *ai_vec_pop(ai_vec *v) {

}

void *ai_vec_pop_at(ai_vec *v, i32 idx) {

}
