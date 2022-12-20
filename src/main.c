#define DEBUG

#include "std.h"
#include "rand.h"

typedef struct sBandit {
  f64 epsilon;
  f64 lr;
  f64 *qTrue;
  f64 *qEstimation;
  u32 k;
} sBandit;

sBandit *fBanditInit(u32 k, f64 epsilon, f64 lr) {
  sBandit *bandit = calloc(1, sizeof(sBandit));
  bandit->epsilon = epsilon;
  bandit->lr = lr;
  bandit->k = k;
  bandit->qEstimation = mCalloc(bandit->qEstimation, k, sizeof(f64));
  bandit->qTrue = mMalloc(bandit->qTrue, k * sizeof(f64));

  return bandit;
}

void fBanditReset(sBandit *self) {
  mFor(i, self->k) {
    self->qTrue[i] = fRandNormal();
  }
  memset(self->qEstimation, 0, self->k * sizeof(f64));
}

u32 fBanditAct(sBandit *self) {
  if (fRandUniform() < self->epsilon) {
    return fRandU32(0, self->k);
  }

  u32 maxAction = 0;
  f64 maxQ = self->qEstimation[0];
  mFor(i, self->k) {
    if (self->qEstimation[i] > maxQ) {
      maxQ = self->qEstimation[i];
      maxAction = i;
    }
  }

  return maxAction;
}

f64 fBanditStep(sBandit *self, u32 action) {
  f64 reward = fRandNormal() + self->qTrue[action];
  self->qEstimation[action] += self->lr * (reward - self->qEstimation[action]);
  return reward;
}

void simulate(u32 runs, u32 times, sBandit **bandits, u32 nBandits) {
  mFor(i, nBandits) {
    f64 *banditRewards = mCalloc(banditRewards, runs, sizeof(f64));
    u32 *banditBestActionCount = mCalloc(banditBestActionCount, runs, sizeof(u32));

    mFor(r, runs) {
      f64 totalRunReward = 0.;
      u32 bestRunActionCount = 0;
      fBanditReset(bandits[i]);

      mFor(t, times) {
        u32 action = fBanditAct(bandits[i]);
        f64 reward = fBanditStep(bandits[i], action);
        totalRunReward += reward;
      }

      banditRewards[r] = totalRunReward / times;
      banditBestActionCount[r] = bestRunActionCount;
    }
  }
}

void trainBandit(void) {
  srand((u32) time(null));

  sBandit **bandits = mMalloc(bandits, 1 * sizeof(sBandit *));
  u32 nBandits = 3;
  u32 runs = 2000;
  u32 times = 1000;
  u32 k = 10;
  f64 lr = 0.1;
  f64 epsilons[3] = {0., 0.1, 0.01};
  mFor(i, nBandits) {
    bandits[i] = fBanditInit(k, epsilons[i], lr);
  }
  simulate(runs, times, bandits, nBandits);
}

f64 track(void (*fn)(void)) {
  clock_t t;
  t = clock();
  fn();
  t = clock() - t;
  return ((f64) t) / CLOCKS_PER_SEC;
}

int main(void) {
  f64 time_taken = track(trainBandit);
  printf("took %f seconds to execute \n", time_taken);
  printf("it/s: %.2f \n", (f64) (2000 * 3) / time_taken);

  return 0;
}