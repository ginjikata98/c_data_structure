//
// Created by DUNG.VM on 28/12/2022.
//

#include "types.h"

u64 ai_std_hash(void* input, i32 len) {
  byte* b = (byte*) input;
  const u64 p = 16777619;
  u64 hash = 2166136261;

  for (int i = 0; i < len; i++)
    hash = (hash ^ b[i]) * p;

  hash += hash << 13;
  hash ^= hash >> 7;
  hash += hash << 3;
  hash ^= hash >> 17;
  hash += hash << 5;

//  u64 hash = 0;
//  for (i32 i = 0; i < len; i++) {
//    hash = (hash << 4) + b[i];
//  }

  return hash;
}