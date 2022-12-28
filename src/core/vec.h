#ifndef MAIN_VEC_H
#define MAIN_VEC_H

#include "types.h"

typedef struct ai_vec ai_vec;
typedef struct ai_vec_api {
  ai_vec* (* empty)(i64 capacity, size element_size);
  i64 (* size)(ai_vec*);
  void* (* get)(ai_vec*, i64 idx);
  void (* push)(ai_vec*, void* value);
  void (* pop)(ai_vec*);
  void (* pop_at)(ai_vec*, i64 idx);
  void* (* to_arr)(ai_vec*);
  void (* push_f32)(ai_vec*, f32);
  f32 (* get_f32)(ai_vec*, i64 idx);
  void (* push_i32)(ai_vec*, i32);
  i32 (* get_i32)(ai_vec*, i64 idx);
} ai_vec_api;

ai_vec* ai_vec_empty(i64 capacity, size element_size);
i64 ai_vec_size(ai_vec*);
void* ai_vec_get(ai_vec*, i64 idx);
void ai_vec_push(ai_vec*, void* value);
void ai_vec_pop(ai_vec*);
void ai_vec_pop_at(ai_vec*, i64 idx);
void* ai_vec_to_arr(ai_vec*);
void ai_vec_push_f32(ai_vec*, f32);
f32 ai_vec_get_f32(ai_vec*, i64 idx);
void ai_vec_push_i32(ai_vec*, i32);
i32 ai_vec_get_i32(ai_vec*, i64 idx);


#define ai_m_vec_module {\
.empty=ai_vec_empty,\
.size=ai_vec_size,\
.get=ai_vec_get,\
.push=ai_vec_push,\
.pop=ai_vec_pop,\
.pop_at=ai_vec_pop_at,   \
.to_arr=ai_vec_to_arr,\
.push_f32=ai_vec_push_f32,\
.get_f32=ai_vec_get_f32,\
.push_i32=ai_vec_push_i32,\
.get_i32=ai_vec_get_i32,\
}                        \

#define ai_m_import_vec(alias) ai_vec_api alias = ai_m_vec_module

#endif //MAIN_VEC_H
