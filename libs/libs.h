//
// Created by DUNG.VM on 25/11/2022.
//

#ifndef C_DATA_STRUCTURE_LIBS_H
#define C_DATA_STRUCTURE_LIBS_H

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

#define null NULL

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef uint8_t byte;

typedef char *String;

typedef struct Node Node;
typedef struct List List;

List *List_init();
bool List_isEmpty(List *list);
void List_print(List *list, void(*printFun)(const void *));
void List_addFirst(List *list, void *item);
void List_addLast(List *list, void *item);
void *List_removeFirst(List *list);
void *List_removeLast(List *list);

#endif //C_DATA_STRUCTURE_LIBS_H
