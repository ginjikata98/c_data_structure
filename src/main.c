#include "core/types.h"
#include "nn/nn.h"

#include "core/function.h"

ai_import_nn(nn);

void *a(void *input, i32 n) {
  printf("wefwefwe");

  return null;
}

int main(void) {

  ai_fn *f = ai_m_calloc(f, 1, sizeof(ai_fn));
  f->data = f;
  f->f = a;

  f->f(null, 10);

  printf("%zu", sizeof(f));

//  ai_module_linear *m = nn.linear(1, 2, 1, ai_module_activation_relu);
//
//  f32 *z = m->base.forward(m, ai_m_vec(f32, 1, 2));
//
//  printf("%f\n", *z);
//
//  ai_module *a2 = ((ai_module*)m);
//
//  printf("%d\n", a2->type);
//  printf("%zu\n", sizeof(ai_module_linear));
//  printf("%zu\n", sizeof(ai_module));

  return 0;
}