//
// Created by DUNG.VM on 28/12/2022.
//

#ifndef MAIN_MAP_H
#define MAIN_MAP_H

#include "types.h"

typedef struct ai_map ai_map;

typedef void (* ai_map_element_free)(void* item);

typedef struct ai_map_api {
  ai_map* (* new)(size ele_size, i64 cap, ai_map_element_free);
  void (* free)(ai_map*);
  void (* clear)(ai_map*);
  i64 (* size)(ai_map*);
  void* (* get)(ai_map*, void* key);
  void (* set)(ai_map*, void* key, void* value);
  void (* delete)(ai_map*, void* key);
} ai_map_api;

#define ai_m_ap_module

#define ai_m_import_map(alias) ai_map_api alias = ai_m_ap_module


#endif //MAIN_MAP_H
