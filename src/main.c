#include "core/types.h"
#include "nn/nn.h"
#include "lib/rand.h"
#include "nn/autograd.h"
#include "core/std.h"

ai_m_import_nn(nn);
ai_m_import_value(v);

ai_m_import_std(std);

f32 fn(f32 x) {
  return 2 * x + 3;
}

i32 f32_compare(const void* a, const void* b) {
  assert(a && b);
  return (i32) (*((f32*) a) - *((f32*) a));
}

int main(void) {
  ai_map* m = std.map.new(sizeof(f32), sizeof(f32), 100, f32_compare, free);

  for (f32 i = 0; i < 100; ++i) {
    f32* vv = ai_m_malloc(vv, sizeof(f32));
    *vv = i;

    std.map.set(m, vv, vv);
  }

  f32 key = 10;
  f32 value = *ai_m_from_byte(std.map.get(m, &key), f32);
  printf("%f\n", value);

  printf("%lld", std.map.size(m));




//  ai_value *a = v.from(5);
//  ai_value *b = v.from(6);
//  ai_value *c = v.pow(v.add(a, b), 2);
//
//  c->backward(c);
////  c->grad = 1;
////  v.backward(c);
//
//  printf("%s\n", v.str(a));
//  printf("%s\n", v.str(b));
//  printf("%s\n", v.str(c));



//  i32 batch = 1000;
//
//  f32 *features = ai_m_calloc(features, batch, sizeof(f32));
//  f32 *target = ai_m_calloc(target, batch, sizeof(f32));
//
//  for (i32 i = 0; i < batch; ++i) {
//    features[i] = ((f32) ai_random_normal()) * ((f32) i);
//    target[i] = fn(features[i]);
//  }
//
//  ai_module *m0 = nn.linear(batch, 1, 4, ai_module_activation_relu);
//  ai_module *m = nn.linear(batch, 4, 1, ai_module_activation_relu);
//  f32 *z = m0->forward(m0, features);
//  z = m->forward(m, z);
//
//  printf("%s\n", m0->str(m0));
//  printf("%s\n", m->str(m));
//
//  f32 loss = 0;
//  for (i32 i = 0; i < batch; ++i) {
//    loss += z[i] - target[i];
////    printf("%d %.4f %.4f %.4f\n", i, features[i], target[i], z[i]);
//  }
//  loss /= batch;
//
//  printf("mean err: %.3f", loss);

  return 0;
}