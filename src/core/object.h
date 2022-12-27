//
// Created by DUNG.VM on 27/12/2022.
//

#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "types.h"

typedef struct ai_object {
  string (*str)(void *);
  i64 (*hash)(void *);
} ai_object;

#endif //MAIN_OBJECT_H
