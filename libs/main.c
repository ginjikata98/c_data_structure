#include <stdio.h>
#include <stdlib.h>
#include "libs.h"


void print(const void *e) {
  printf("%d\n", *((int *) e));
}

int main(void) {

  u32 a1 = 1;
  u32 a2 = 2;
  u32 a3 = 3;

  List *list = List_init();
  List_addFirst(list, &a1);
  List_addLast(list, &a2);
  List_addFirst(list, &a3);
  List_removeFirst(list);
  List_removeLast(list);

  List_print(list, print);
  return 0;

}