#ifndef __TRAJECTORY_H__
#define __TRAJECTORY_H__

#include <iostream>
#include <vector>
#include "base.h"
#include "state.h"
#include "input.h"
#include "pendulum.h"
#include "swing.h"
#include "planner.h"

namespace Capt {

class Trajectory {
public:
  Trajectory(Model *model);
  ~Trajectory();

  void set(EnhancedInput input, Foot suf);

  vec3_t getCop(double elapsed);
  vec3_t getIcp(double elapsed);
  vec3_t getFootR(double elapsed);
  vec3_t getFootL(double elapsed);

private:
  EnhancedInput input;

  Pendulum pendulum;
  Swing    swing;

  double h, dt_min;
  double elapsed, planned;
  Foot   suf;
  double time;
};

} // namespace Capt

#endif // __TRAJECTORY_H__