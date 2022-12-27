//
// Created by Tony Vu on 27/12/2022.
//

#ifndef MAIN_SRC_CORE_FUNCTION_H_
#define MAIN_SRC_CORE_FUNCTION_H_

#include "types.h"

typedef struct ai_fn {
  void *data;
  void *(*f)(void *input=data, i32 n);
  void *(*call)(void *input, i32 n);
} ai_fn;

#endif //MAIN_SRC_CORE_FUNCTION_H_
