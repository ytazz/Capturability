#ifndef __PENDULUM_H__
#define __PENDULUM_H__

#include "loader.h"
#include "model.h"
#include "base.h"

namespace Capt {

class Pendulum {

public:
  Pendulum(Model *model);
  ~Pendulum();

  void setCom(const vec2_t com);
  void setCom(const vec3_t com);
  void setComVel(const vec2_t com_vel);
  void setComVel(const vec3_t com_vel);
  void setIcp(const vec2_t icp);
  void setIcp(const vec3_t icp);
  void setCop(const vec2_t cop);
  void setCop(const vec3_t cop);

  vec2_t getCop   (float t);
  vec2_t getCom   (float t);
  vec2_t getComVel(float t);
  vec2_t getIcp   (float t);
  vec2_t getIcpVel(float t);

  // inverse time
  //   - icp: icp_before_move
  //   - hat_icp: icp_after_move
  // calculate equivalent cop
  //vec2_t invCop(vec2_t icp, vec2_t hat_icp, float dt);
  // calculate equivalent icp(0)
  //vec2_t invIcp(vec2_t cop, vec2_t hat_icp, float dt);

private:
  vec2_t com, com_vel;
  vec2_t icp;
  vec2_t cop;
  float  g;
  float  h;
  float  omega;
};

} // namespace Capt

#endif // __PENDULUM_H__