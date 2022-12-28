//
// Created by DUNG.VM on 28/12/2022.
//

#include "map.h"
#include "vec.h"

typedef struct ai_map_node {
  size key_size;
  size val_size;
  byte buf[];
} ai_map_node;

struct ai_map {
  i64 cap;
  i64 len;
  ai_vec* buckets;
};


ai_map* ai_map_new(size ele_size, i64 cap, ai_map_element_compare, ai_map_element_free) {

}

void ai_map_free(ai_map*) {

}

void ai_map_clear(ai_map*) {

}

i64 ai_map_size(ai_map*) {

}

void* ai_map_get(ai_map*, void* key) {

}

void ai_map_set(ai_map*, void* key, void* value) {

}

void ai_map_delete(ai_map*, void* key) {

}
