//
// Created by DUNG.VM on 25/11/2022.
//

#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define null NULL

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t byte;

typedef char *String;


typedef struct ListNode {
  void *item;
  struct ListNode *next;
  struct ListNode *prev;
} ListNode;

typedef struct List {
  ListNode *head, *tail;
  u32 length;
} List;

List *List_init();

void List_push(List *list, void *item);

#endif //C_DATA_STRUCTURE_LIBS_H
