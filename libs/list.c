//
// Created by DUNG.VM on 25/11/2022.
//
#include "libs.h"


List *List_init() {
  List *list = (List *) malloc(sizeof(List));
  assert(list != null);
  list->head = list->tail = null;
  list->length = 0;
  return list;
}

void List_push(List *list, void *item) {

}
