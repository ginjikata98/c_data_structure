#ifndef MAIN_NN_H
#define MAIN_NN_H

#include "../lib/std.h"

struct sModule;
typedef struct sModule sModule;

struct sNetwork;
typedef struct sNetwork sNetwork;

typedef enum {
  emModuleTypeLinear, emModuleTypeSoftmax, emModuleTypeDropout,


  emModuleTypeMaxSize,
} eModuleType;

typedef enum {
  emModuleActivationRelu, emModuleActivationSigmoid, emModuleActivationTanh,

  emModuleActivationMaxSize,
} eModuleActivation;


struct sModule {
  string name;
  eModuleType type;
  eModuleActivation activation;
  void (*forward)(struct sModule, struct sNetwork);
  void (*backward)(struct sModule, struct sNetwork);
  void (*update)(struct sModule);
  void *config;
};

struct sNetwork {
  string name;
  i32 numModules;
  sModule *modules;
};


#endif //MAIN_NN_H
