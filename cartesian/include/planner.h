#ifndef __PLANNER_H__
#define __PLANNER_H__

#include "model.h"
#include "param.h"
#include "config.h"
#include "grid.h"
#include "capturability.h"
#include "tree.h"
#include "search.h"
#include "swing.h"
#include "pendulum.h"
#include <iostream>
#include <chrono>
#include <vector>

namespace Capt {

#if 0
class Planner {
public:
  Planner(Model *model, Param *param, Config *config, Grid *grid, Capturability *capt);
  ~Planner();

  void                  set(EnhancedState state);
  EnhancedInput         get();
  std::vector<Sequence> getSequence();
  arr3_t                getFootstepR();
  arr3_t                getFootstepL();
  std::vector<CaptData> getCaptureRegion();

  void clear();

  Status plan();

private:
  void   calculateStart();
  bool   calculateGoal();
  Status runSearch(int preview);

  Tree     *tree;
  Search   *search;
  Swing    *swing;
  Pendulum *pendulum;

  EnhancedState state;
  EnhancedInput input;

  // start
  Foot   s_suf;
  vec3_t rfoot, lfoot, icp;
  vec3_t suf, swf;
  // goal
  Foot   g_suf;
  arr2_t posRef, icpRef;

  float  dt, dt_min;
  int    preview;

  bool found;
};
#endif

} // namespace Capt

#endif // __PLANNER_H__