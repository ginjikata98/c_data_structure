#include <stdio.h>
#include <stdlib.h>
#include <tensorflow/c/c_api.h>

#define DEBUG

#include "macros.h"

f64 square(f64 x) {
  return x * x * x;
}

f64 grad(f64 (*f)(f64), f64 x) {
  return (f(x + 1e-6) - f(x - 1e-6)) / (2e-6);
}

typedef struct NDArray {
  byte *data;
  u32 numOfDim;
  u32 *dimensions;
  u32 *strides;
} NDArray;


void NoOpDeallocator(void *data, size_t a, void *b) {}


void tf() {
  printf("Hello from TensorFlow C library version %s\n", TF_Version());

  TF_Graph *Graph = TF_NewGraph();
  TF_Status *Status = TF_NewStatus();
  TF_SessionOptions *SessionOpts = TF_NewSessionOptions();
  TF_Buffer *RunOpts = NULL;

  i64 dims[] = {1, 1};
  f32 data[] = {1, 2, 3, 4};
  int ndata = sizeof(data);

  TF_Tensor *t = TF_NewTensor(TF_FLOAT, dims, 2, data, ndata, &NoOpDeallocator, 0);
  ASSERT(t != null);

}

int main(void) {
//  List_f64 a;
//  List_init(&a);
//
//  Node_f64 n;
//  Node_init(n, Node_f64);


  return 0;
}