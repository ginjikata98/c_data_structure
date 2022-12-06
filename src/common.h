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
void List_clear(List *list);
void List_destroy(List *list);
void List_print(List *list, void(*printFun)(const void *));
void List_addFirst(List *list, void *item);
void List_addLast(List *list, void *item);
void *List_removeFirst(List *list);
void *List_removeLast(List *list);

#define Vec(T) typedef struct { u32 size; u32 capacity; T *items;  } Vec_##T

#define Vec_init(v, cap) \
memset((v), 0, sizeof(*(v))); \
(v)->capacity = (cap) == 0 ? 16 : (cap);                         \
(v)->items = calloc((cap), sizeof((v)->items[0]));       \
assert((v)->items != null)

#define Vec_destroy(v) free((v)->items); (v)->items=null

#define Vec_add(v, e) \
if ((v)->size == (v)->capacity) { \
  (v)->items = realloc((v)->items, (v)->capacity * 2 * sizeof((v)->items[0])); \
  assert((v)->items != null);\
  (v)->capacity *= 2; \
}                      \
(v)->items[(v)->size++] = e


Vec(u32);
Vec(i64);
Vec(String);


#endif //C_DATA_STRUCTURE_LIBS_H
