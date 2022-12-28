//
// Created by DUNG.VM on 28/12/2022.
//

#include "map.h"

typedef struct ai_map_node {
  void* key;
  void* value;
  struct ai_map_node* next;
  struct ai_map_node* prev;
} ai_map_node;

struct ai_map {
  i64 len;
  i64 bucket_size;
  size key_size;
  size val_size;
  ai_map_element_compare compare;
  ai_map_element_free ele_free;
  ai_map_node** buckets;
};

static i64 ai_map_get_bucket_pos(ai_map* m, void* bytes, i32 len) {
  return ai_std_hash(bytes, len) % m->bucket_size;
}


ai_map*
ai_map_new(size key_size, size val_size, i64 bucket_size, ai_map_element_compare cmp, ai_map_element_free ele_free) {
  assert(cmp && ele_free && bucket_size > 0);
  ai_map* map = ai_m_malloc(map, sizeof(*map));
  map->len = 0;
  map->bucket_size = bucket_size;
  map->key_size = key_size;
  map->val_size = val_size;
  map->compare = cmp;
  map->ele_free = ele_free;
  map->buckets = ai_m_malloc(map->buckets, sizeof(ai_map_node*));
  return map;
}

void ai_map_free(ai_map* m) {
//  assert(m);
//  for (int i = 0; i < ; ++i) {
//
//  }

}

void ai_map_clear(ai_map* m) {

}

i64 ai_map_size(ai_map* m) {
  assert(m);
  return m->len;
}

void* ai_map_get(ai_map* m, void* key) {
  assert(m && key);
  i64 pos = ai_map_get_bucket_pos(m, key, m->key_size);
  ai_map_node* list = m->buckets[pos];
  ai_map_node* temp = list;

  while (temp) {
    if (m->compare(temp->key, key)) {
      return temp->value;
    }
    temp = temp->next;
  }
  return null;
}

void ai_map_set(ai_map* m, void* key, void* value) {
  assert(m && key);
  ai_map_node* node = ai_m_malloc(node, sizeof(ai_map_node));
  node->key = key;
  node->value = value;
  node->next = null;
  node->prev = null;

  i64 pos = ai_map_get_bucket_pos(m, key, m->key_size);
  ai_map_node* list = m->buckets[pos];
  ai_map_node* temp = list;

  while (temp) {
    if (m->compare(temp->key, key)) {
      temp->value = value;
      return;
    }
    temp = temp->next;
  }

  node->next = list;
  if (list) {
    list->prev = node;
  }
  m->buckets[pos] = node;
}

void ai_map_delete(ai_map* m, void* key) {
  assert(m && key);
  i64 pos = ai_map_get_bucket_pos(m, key, m->key_size);
  ai_map_node* list = m->buckets[pos];
  ai_map_node* temp = list;

  while (temp) {
    if (m->compare(temp->key, key)) {
      ai_map_node* next = temp->next;
      ai_map_node* prev = temp->prev;

      if (next) {
        next->prev = prev;
      }

      if (prev) {
        prev->next = next;
      }

      m->ele_free(temp);

      return;
    }
    temp = temp->next;
  }
}
