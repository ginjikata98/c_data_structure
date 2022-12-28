#include "vec.h"

struct ai_vec {
  i64 idx;
  i64 cap;
  size ele_size;
  byte buf[];
};


ai_vec* ai_vec_empty(i64 capacity, size element_size) {
  assert(capacity > 0);
  ai_vec* v = ai_m_malloc(v, sizeof(ai_vec) + capacity * element_size);
  v->cap = capacity * element_size;
  v->ele_size = element_size;
  return v;
}

void* ai_vec_get(ai_vec* v, i64 idx) {
  assert(v && idx >= 0 && v->idx >= v->ele_size * idx);
  return (void*) (v->buf + idx * v->ele_size);
}

void ai_vec_push(ai_vec* v, void* value) {
  assert(v && value);

  if (v->idx == v->cap) {
    v = ai_m_realloc(v, sizeof(ai_vec) + v->cap * 2);
    v->cap *= 2;
  }

  memcpy(v->buf + v->idx, value, v->ele_size);
  v->idx += v->ele_size;
}

i64 ai_vec_size(ai_vec* v) {
  assert(v);
  return v->idx / v->ele_size;
}


void ai_vec_pop(ai_vec* v) {
  assert(v && v->idx);
  v->idx -= v->ele_size;
}

void ai_vec_pop_at(ai_vec* v, i64 idx) {
  assert(v && v->idx > 0 && idx >= 0 && idx * v->ele_size < v->idx);
  idx *= v->ele_size;
  memmove(v->buf + idx, v->buf + idx + v->ele_size, v->idx - v->ele_size);
  v->idx -= v->ele_size;
}

void* ai_vec_to_arr(ai_vec* v) {
  assert(v && v->idx);
  return v->buf;
}

void ai_vec_push_f32(ai_vec* v, f32 value) {
  assert(v->ele_size == sizeof(f32));
  ai_vec_push(v, &value);
}

f32 ai_vec_get_f32(ai_vec* v, i64 idx) {
  return *ai_m_from_byte(ai_vec_get(v, idx), f32);
}

void ai_vec_push_i32(ai_vec* v, i32 value) {
  assert(v->ele_size == sizeof(i32));
  ai_vec_push(v, &value);
}

i32 ai_vec_get_i32(ai_vec* v, i64 idx) {
  return *ai_m_from_byte(ai_vec_get(v, idx), i32);
}

void ai_vec_pop_swap(ai_vec* v, i64 idx) {
  assert(v && v->idx > 0 && idx >= 0 && idx * v->ele_size < v->idx);
  idx *= v->ele_size;
  v->idx -= v->ele_size;
  memcpy(v->buf + idx, v->buf + v->idx, v->ele_size);
}
