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

  TF_Graph *graph = TF_NewGraph();
  TF_Status *status = TF_NewStatus();
  TF_SessionOptions *sessionOpts = TF_NewSessionOptions();
  TF_Buffer *RunOpts = NULL;
  TF_Session *session = TF_NewSession(graph, sessionOpts, status);

  i64 dims[] = {1, 1};
  f32 data[] = {1, 2, 3, 4};
  int dataSize = sizeof(data);

  TF_Tensor *t = TF_NewTensor(TF_FLOAT, dims, 2, data, dataSize, &NoOpDeallocator, 0);
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