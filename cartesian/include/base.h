#ifndef __BASE_H__
#define __BASE_H__

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

namespace Capt {

typedef Eigen::Vector2f vec2_t;
typedef Eigen::Vector2i vec2i_t;
typedef Eigen::Vector3d vec3_t;
typedef std::vector<vec2_t> arr2_t;
typedef std::vector<vec3_t> arr3_t;

double dot(vec2_t v1, vec2_t v2);
double cross(vec2_t v1, vec2_t v2);
vec2_t normal(vec2_t v);
vec2_t mirror(vec2_t v);
vec3_t mirror(vec3_t v);

double min(double val1, double val2);
double max(double val1, double val2);

int round(double val);

vec3_t vec2Tovec3(vec2_t vec2);
vec2_t vec3Tovec2(vec3_t vec3);

bool inIndexList(int id, std::vector<int> ids);

enum OccupancyType {
  NONE,
  EMPTY,
  EXIST,
  CLOSED,
  GOAL
};

enum Foot { FOOT_NONE, FOOT_R, FOOT_L };

struct Step {
  Foot   suf;
  vec3_t pos;
  vec3_t cop;
  vec3_t icp;
  // vec3_t com;
};

enum Status { SUCCESS, FAIL, FINISH };

typedef std::vector<Step> Footstep;

struct Sequence {
  Foot   suf;
  vec3_t pos;
  vec3_t icp;
  vec3_t cop;

  void substitute(Foot suf, vec2_t pos, vec2_t icp, vec2_t cop){
    this->suf     = suf;
    this->pos.x() = pos.x();
    this->pos.y() = pos.y();
    this->pos.z() = 0.0;
    this->icp.x() = icp.x();
    this->icp.y() = icp.y();
    this->icp.z() = 0.0;
    this->cop.x() = cop.x();
    this->cop.y() = cop.y();
    this->cop.z() = 0.0;
  }
};

struct EnhancedState {
  Capt::Footstep footstep;
  Capt::vec3_t   icp;
  Capt::vec3_t   rfoot;
  Capt::vec3_t   lfoot;
  double         elapsed;
  Capt::Foot     s_suf;

  void operator=(const EnhancedState &eState) {
    this->footstep = eState.footstep;
    this->icp      = eState.icp;
    this->rfoot    = eState.rfoot;
    this->lfoot    = eState.lfoot;
    this->elapsed  = eState.elapsed;
    this->s_suf    = eState.s_suf;
  }

  void print(){
    printf("EnhancedState\n");
    if(s_suf == Foot::FOOT_R) {
      printf("  support: Right\n");
    }else{
      printf("  support: Left\n");
    }
    printf("  elapsed: %1.4lf\n", elapsed);
    printf("  icp    : %1.3lf, %1.3lf, %1.3lf\n", icp.x(), icp.y(), icp.z() );
    printf("  rfoot  : %1.3lf, %1.3lf, %1.3lf\n", rfoot.x(), rfoot.y(), rfoot.z() );
    printf("  lfoot  : %1.3lf, %1.3lf, %1.3lf\n", lfoot.x(), lfoot.y(), lfoot.z() );
  }
};

struct EnhancedInput {
  double       elapsed;  // elapsed time from support foot exchange
  double       duration; // remained step duration
  Capt::vec3_t cop;
  Capt::vec3_t icp;
  Capt::vec3_t suf;
  Capt::vec3_t swf;
  Capt::vec3_t land;

  void operator=(const EnhancedInput &eInput) {
    this->elapsed  = eInput.elapsed;
    this->duration = eInput.duration;
    this->cop      = eInput.cop;
    this->icp      = eInput.icp;
    this->suf      = eInput.suf;
    this->swf      = eInput.swf;
    this->land     = eInput.land;
  }

  void print(){
    printf("EnhancedInput\n");
    printf("  elapsed : %1.4lf\n", elapsed);
    printf("  duration: %1.4lf\n", duration);
    printf("  cop     : %1.3lf, %1.3lf, %1.3lf\n", cop.x(), cop.y(), cop.z() );
    printf("  icp     : %1.3lf, %1.3lf, %1.3lf\n", icp.x(), icp.y(), icp.z() );
    printf("  suf     : %1.3lf, %1.3lf, %1.3lf\n", suf.x(), suf.y(), suf.z() );
    printf("  swf     : %1.3lf, %1.3lf, %1.3lf\n", swf.x(), swf.y(), swf.z() );
    printf("  land    : %1.3lf, %1.3lf, %1.3lf\n", land.x(), land.y(), land.z() );
  }
};

} // namespace Capt

#endif // __BASE_H__