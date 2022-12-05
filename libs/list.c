//
// Created by DUNG.VM on 25/11/2022.
//
#include "libs.h"


struct Node {
  void *item;
  struct Node *next;
  struct Node *prev;
};

struct List {
  Node *head, *tail;
  u32 length;
};

List *List_init() {
  List *list = (List *) malloc(sizeof(List));
  assert(list != null);
  list->head = list->tail = null;
  list->length = 0;
  return list;
}

bool List_isEmpty(List *list) {
  assert(list != null);
  return list->length == 0;
}

void List_print(List *list, void(*printFun)(const void *)) {
  assert(list != null && printFun != null);
  Node *currentNode = list->head;
  while (currentNode != null) {
    printFun(currentNode->item);
    currentNode = currentNode->next;
  }
}

void List_addFirst(List *list, void *item) {
  assert(list != null && item != null);
  Node *newNode = (Node *) malloc(sizeof(Node));
  assert(newNode != null);
  newNode->item = item;
  newNode->next = list->head;
  newNode->prev = null;

  if (List_isEmpty(list)) {
    list->tail = newNode;
  } else {
    list->head->prev = newNode;
  }

  list->head = newNode;
  list->length++;
}

void List_addLast(List *list, void *item) {
  assert(list != null && item != null);
  Node *newNode = (Node *) malloc(sizeof(Node));
  assert(newNode != null);
  newNode->item = item;
  newNode->next = null;
  newNode->prev = list->tail;

  if (List_isEmpty(list)) {
    list->head = newNode;
  } else {
    list->tail->next = newNode;
  }

  list->tail = newNode;
  list->length++;
}

void *List_removeFirst(List *list) {
  assert(list != null);
  Node *nodeToFree = list->head;
  if (List_isEmpty(list)) {
    return null;
  }

  if (list->head == list->tail) {
    list->head = list->tail = null;
  } else {
    list->head = list->head->next;
    list->head->prev = null;
  }
  list->length--;
  void *returnItem = nodeToFree->item;
  free(nodeToFree);
  return returnItem;
}

void *List_removeLast(List *list) {
  assert(list != null);
  Node *nodeToFree = list->tail;
  if (List_isEmpty(list)) {
    return null;
  }

  if (list->head == list->tail) {
    list->head = list->tail = null;
  } else {
    list->tail = list->tail->prev;
    list->tail->next = null;
  }
  list->length--;
  void *returnItem = nodeToFree->item;
  free(nodeToFree);
  return returnItem;
}
