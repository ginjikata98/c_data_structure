#ifndef MAIN_VEC_H
#define MAIN_VEC_H

#include "types.h"

typedef struct ai_vec ai_vec;


ai_vec *ai_vec_empty(i32 capacity, size element_size);
void *ai_vec_get(ai_vec *, i32 idx);
void ai_vec_push(ai_vec *, byte *value);
void *ai_vec_pop(ai_vec *);
void *ai_vec_pop_at(ai_vec *, i32 idx);

#endif //MAIN_VEC_H
