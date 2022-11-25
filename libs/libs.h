//
// Created by DUNG.VM on 25/11/2022.
//

#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include <stdlib.h>
#include <stddef.h>

typedef struct ListNode {
  void *data;
  struct ListNode *next;
  struct ListNode *prev;
} ListNode;

typedef struct List {
  ListNode *head, *tail;
  int size;
  size_t elementSize;
} List;

List *List_init();

void List_push(List *list, void *item);

#endif //C_DATA_STRUCTURE_LIBS_H
