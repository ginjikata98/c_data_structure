//
// Created by DUNG.VM on 28/12/2022.
//

#ifndef MAIN_MAP_H
#define MAIN_MAP_H

#include "types.h"

typedef struct ai_map ai_map;

typedef i32(* ai_map_element_compare)(const void* a, const void* b);
typedef void (* ai_map_element_free)(void* item);

typedef struct ai_map_api {
  ai_map* (* new)(size key_size, size val_size, i64 bucket_size, ai_map_element_compare, ai_map_element_free);
  void (* free)(ai_map*);
  void (* clear)(ai_map*);
  i64 (* size)(ai_map*);
  void* (* get)(ai_map*, void* key);
  void (* set)(ai_map*, void* key, void* value);
  void (* delete)(ai_map*, void* key);
} ai_map_api;

ai_map* ai_map_new(size key_size, size val_size, i64 bucket_size, ai_map_element_compare, ai_map_element_free);
void ai_map_free(ai_map*);
void ai_map_clear(ai_map*);
i64 ai_map_size(ai_map*);
void* ai_map_get(ai_map*, void* key);
void ai_map_set(ai_map*, void* key, void* value);
void ai_map_delete(ai_map*, void* key);


#define ai_m_ap_module {\
.new=ai_map_new,\
.free=ai_map_free,\
.clear=ai_map_clear,\
.size=ai_map_size,\
.get=ai_map_get,\
.set=ai_map_set,\
.delete=ai_map_delete,\
}\

#define ai_m_import_map(alias) ai_map_api alias = ai_m_ap_module


#endif //MAIN_MAP_H
