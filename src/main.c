#define DEBUG

#include "std.h"
#include "ndarray.h"
#include "rand.h"

typedef struct sBandit {
  f64 epsilon;
  f64 lr;
  f64 trueReward;
  f64 *qTrue;
  f64 *qEstimation;
  u32 *actionCount;
  u32 k;
  u32 bestAction;
} sBandit;

sBandit *fBanditInit(u32 k, f64 epsilon, f64 lr, f64 trueReward) {
  sBandit *bandit = calloc(1, sizeof(sBandit));
  bandit->epsilon = epsilon;
  bandit->lr = lr;
  bandit->k = k;
  bandit->trueReward = trueReward;
  bandit->actionCount = mCalloc(bandit->actionCount, k, sizeof(u32));
  bandit->qTrue = mMalloc(bandit->qTrue, k * sizeof(f64));
  bandit->qEstimation = mCalloc(bandit->qEstimation, k, sizeof(f64));

  return bandit;
}

void fBanditReset(sBandit *self) {
  mFor(i, self->k) {
    self->qTrue[i] = fRandNormal() + self->trueReward;
    self->qEstimation[i] = 0;
    self->actionCount[i] = 0;
  }

}

u32 fBanditAct(sBandit *self) {
  if (fRandUniform() < self->epsilon) {
    return fRandU32(0, self->k);
  }

  u32 maxAction = 0;
  f64 maxQ = -100;
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
  self->actionCount[action]++;
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
        if (action == bandits[i]->bestAction) {
          bestRunActionCount++;
        }
      }

      banditRewards[r] = totalRunReward / times;
      banditBestActionCount[r] = bestRunActionCount;
    }

  }
}

int main(void) {
  srand(time(null));

  clock_t t;
  t = clock();

  sBandit **bandits = mMalloc(bandits, 1 * sizeof(sBandit *));
  u32 nBandits = 3;
  u32 runs = 2000;
  u32 times = 1000;
  f64 epsilons[3] = {0., 0.1, 0.01};
  mFor(i, nBandits) {
    bandits[i] = fBanditInit(10, epsilons[i], 0.1, 0);
  }
  simulate(runs, times, bandits, nBandits);

  t = clock() - t;
  double time_taken = ((double) t) / CLOCKS_PER_SEC;
  printf("took %f seconds to execute \n", time_taken);
  printf("it/s: %.2f \n", (f64) (runs * nBandits) / time_taken);

  return 0;
}