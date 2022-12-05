#include <stdio.h>
#include <stdlib.h>
#include "libs.h"


void print(const void *e) {
  printf("%d\n", *((u32 *) e));
}

u32 *generateIntPointerDLLT(u32 integer) {
  u32 *newInt = (u32 *) malloc(sizeof(u32));
  *newInt = integer;
  return newInt;
}

int main(void) {
  List *list = List_init();
  for (u32 i = 0; i < 10; ++i) {
    List_addLast(list, generateIntPointerDLLT(i));
  }

  List_print(list, print);
  return 0;

}