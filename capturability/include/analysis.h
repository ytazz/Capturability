#ifndef __ANALYSIS_H__
#define __ANALYSIS_H__

#include "capturability.h"
#include "grid.h"
#include "input.h"
#include "model.h"
#include "param.h"
#include "pendulum.h"
#include "state.h"
#include "swing_foot.h"
#include "vector.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <vector>

namespace CA {

struct CaptureState {
  int n_capturable;
  GridState grid_state;
  GridInput grid_input;

  void operator=(const CaptureState &capture_state) {
    this->grid_state = capture_state.grid_state;
    this->grid_input = capture_state.grid_input;
  }
};

class Analysis {

public:
  Analysis(Model model, Param param);
  ~Analysis();

  void exe(int n_step);
  void save(const char *file_name, const int n_step_capturable);

  State step(const State state, const Input input);

private:
  void exe0();
  void exeN(int n_step);

  void progress(int state_id);

  Grid grid;
  Model model;
  Pendulum pendulum;
  SwingFoot swing_foot;
  Capturability capturability;

  // save calculation log
  FILE *fp;

  vec2_t cop;
  float step_time;

  std::vector<std::vector<bool>> is_database;
};

} // namespace CA

#endif // __ANALYSIS_H__