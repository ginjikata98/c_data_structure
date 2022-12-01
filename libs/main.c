#include <stdio.h>
#include <stdlib.h>
#include "libs.h"


void print(const void *e) {
  printf("%d\n", *((int *) e));
}

int main(void) {

  u32 a = 10;

  List *list = List_init();
  List_addFirst(list, &a);
  List_addLast(list, &a);

  List_print(list, print);
  return 0;

}