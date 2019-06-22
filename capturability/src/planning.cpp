#include "planning.h"

namespace CA {

Planning::Planning(Model model, Param param)
    : polygon(), pendulum(model), capturability(model, param), grid(param),
      swing_foot(model) {
  this->com = vec3_t::Zero();
  this->com_vel = vec3_t::Zero();
  this->rleg = vec3_t::Zero();
  this->lleg = vec3_t::Zero();
  this->com_ref = vec3_t::Zero();
  this->com_vel_ref = vec3_t::Zero();
  this->rleg_ref = vec3_t::Zero();
  this->lleg_ref = vec3_t::Zero();

  g = model.getVal("environment", "gravity");
  h = model.getVal("physics", "com_height");
  omega = sqrt(g / h);

  capturability.load("1step.csv");
}

Planning::~Planning() {}

void Planning::setCom(vec3_t com) { this->com = com; }

void Planning::setComVel(vec3_t com_vel) { this->com_vel = com_vel; }

void Planning::setRLeg(vec3_t rleg) { this->rleg = rleg; }

void Planning::setLLeg(vec3_t lleg) { this->lleg = lleg; }

vec3_t Planning::vec2tovec3(vec2_t vec2) {
  vec3_t vec3;
  vec3.x() = vec2.x;
  vec3.y() = vec2.y;
  vec3.z() = 0.0;
  return vec3;
}

vec2_t Planning::vec3tovec2(vec3_t vec3) {
  vec2_t vec2;
  vec2.setCartesian(vec3.x(), vec3.y());
  return vec2;
}

void Planning::calcRef() {
  // get capture region
  vec3_t icp3 = com + com_vel / omega;
  std::cout << "com" << '\n';
  std::cout << com << '\n';
  std::cout << "com_vel" << '\n';
  std::cout << com_vel << '\n';

  State state;
  state.icp.setCartesian((icp3 - rleg).x(), (icp3 - rleg).y());
  state.swft.setCartesian((lleg - rleg).x(), (lleg - rleg).y());
  state.printCartesian();

  GridState gstate;
  gstate = grid.roundState(state);

  std::vector<CA::CaptureSet> capture_set;
  capture_set = capturability.getCaptureRegion(gstate.id, 1);
  // printf("capture region\n");
  // for (size_t i = 0; i < capture_set.size(); i++) {
  //   printf("%f,%f\n", capture_set[i].swft.x, capture_set[i].swft.y);
  // }

  // calculate desired landing position
  vec3_t landing;
  float dist = 0.0, dist_min = 0.0;
  int dist_min_id = 0;
  std::cout << "size = " << capture_set.size() << '\n';
  for (size_t i = 0; i < capture_set.size(); i++) {
    dist = (capture_set[i].swft - state.swft).norm();
    if (i == 0) {
      dist_min = dist;
      dist_min_id = i;
    } else if (dist < dist_min) {
      dist_min = dist;
      dist_min_id = i;
    }
  }
  landing.x() = capture_set[dist_min_id].swft.x;
  landing.y() = capture_set[dist_min_id].swft.y;
  landing.z() = 0.0;
  std::cout << "landing" << '\n';
  std::cout << landing << '\n';

  // feet trajectory planning
  swing_foot.set(lleg, rleg + landing);
  step_time = swing_foot.getTime();

  // com trajectory planning
  cop = capture_set[dist_min_id].cop + vec3tovec2(rleg);
  pendulum.setCom(com);
  pendulum.setComVel(com_vel);
  pendulum.setCop(cop);
  com_ = vec2tovec3(pendulum.getCom(step_time));
  com_vel_ = vec2tovec3(pendulum.getComVel(step_time));
}

vec2_t Planning::getCop(float time) {
  vec2_t current_cop;
  if (time <= step_time) {
    current_cop = cop;
  } else {
    current_cop = getIcp(time);
    cop_ = getIcp(time);
  }
  return current_cop;
}

vec3_t Planning::getCom(float time) {
  vec2_t com2_ref;
  if (time <= step_time) {
    pendulum.setCom(com);
    pendulum.setComVel(com_vel);
    pendulum.setCop(cop);
    com2_ref = pendulum.getCom(time);
  } else {
    pendulum.setCom(com_);
    pendulum.setComVel(com_vel_);
    pendulum.setCop(cop_);
    com2_ref = pendulum.getCom(time - step_time);
  }
  com_ref = vec2tovec3(com2_ref);
  com_ref.z() = h;
  return com_ref;
}

vec3_t Planning::getComVel(float time) {
  vec2_t com_vel2_ref;
  if (time <= step_time) {
    pendulum.setCom(com);
    pendulum.setComVel(com_vel);
    pendulum.setCop(cop);
    com_vel2_ref = pendulum.getComVel(time);
  } else {
    pendulum.setCom(com_);
    pendulum.setComVel(com_vel_);
    pendulum.setCop(cop_);
    com_vel2_ref = pendulum.getComVel(time - step_time);
  }
  com_vel_ref = vec2tovec3(com_vel2_ref);
  com_vel_ref.z() = 0.0;
  return com_vel_ref;
}

vec2_t Planning::getIcp(float time) {
  icp_ref.setCartesian(getCom(time).x() + getComVel(time).x() / omega,
                       getCom(time).y() + getComVel(time).y() / omega);
  return icp_ref;
}

vec3_t Planning::getRLeg(float time) {
  rleg_ref = rleg;
  if (time > step_time) {
    rleg_ref.y() += 0.00001;
    rleg_ref.z() += 0.00001;
  }
  return rleg_ref;
}

vec3_t Planning::getLLeg(float time) {
  if (time <= step_time)
    lleg_ref = swing_foot.getTraj(time);
  return lleg_ref;
}

} // namespace CA