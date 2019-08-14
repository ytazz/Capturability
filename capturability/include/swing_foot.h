#ifndef __SWING_FOOT_H__
#define __SWING_FOOT_H__

// #include "interpolation.h"
#include "cycloid.h"
#include "model.h"
#include "vector.h"

namespace Capt {

class SwingFoot {
public:
  SwingFoot(Model model);
  ~SwingFoot();

  void   set(vec2_t foot, vec2_t foot_des);
  void   set(vec3_t foot, vec3_t foot_des);
  float  getTime();
  vec3_t getTraj(float dt);

private:
  Cycloid cycloid;

  vec3_t foot, foot_des;
  float  step_time_min, step_time;
  float  step_height;
  float  foot_vel;
};

} // namespace Capt

#endif // __SWING_FOOT_H__
