#ifndef __INPUT_H__
#define __INPUT_H__

#include "base.h"
#include <iostream>
#include <string>

namespace Capt {

struct Input {
  vec2_t cop, swf;

  Input(){
  }
  Input(double cop_x, double cop_y, double swf_x, double swf_y){
    set(cop_x, cop_y, swf_x, swf_y);
  }
  Input(vec2_t cop, vec2_t swf){
    set(cop, swf);
  }

  void set(double cop_x, double cop_y, double swf_x, double swf_y){
    this->cop.x() = cop_x;
    this->cop.y() = cop_y;
    this->swf.x() = swf_x;
    this->swf.y() = swf_y;
  }

  void set(vec2_t cop, vec2_t swf){
    this->cop = cop;
    this->swf = swf;
  }

  void print() {
    printf("cop = [ %lf, %lf ]\n", cop.x(), cop.y() );
    printf("swf = [ %lf, %lf ]\n", swf.x(), swf.y() );
  }

  void operator=(const Input &input) {
    this->cop = input.cop;
    this->swf = input.swf;
  }
};

} // namespace Capt

#endif // __INPUT_H__