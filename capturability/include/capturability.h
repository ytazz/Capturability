#ifndef __CAPTURABILITY_H__
#define __CAPTURABILITY_H__

#include "grid.h"
#include "input.h"
#include "model.h"
#include "param.h"
#include "polygon.h"
#include "state.h"
#include "swing_foot.h"
#include <iostream>
#include <stdio.h>
#include <vector>

namespace Capt {

enum DataType { BASIN, NSTEP, COP, STEPTIME };

struct CaptureSet {
  int state_id;
  int input_id;
  int next_id;
  int nstep;

  vec2_t cop;
  double step_time;

  void operator=(const CaptureSet &capture_set) {
    this->state_id  = capture_set.state_id;
    this->input_id  = capture_set.input_id;
    this->next_id   = capture_set.next_id;
    this->nstep     = capture_set.nstep;
    this->cop       = capture_set.cop;
    this->step_time = capture_set.step_time;
  }
};

class Capturability {
public:
  Capturability(Model model, Param param);
  ~Capturability();

  void load(std::string file_name, DataType type);

  CaptureSet* getCaptureSet(int state_id, int input_id);

  std::vector<CaptureSet> getCaptureRegion(const int state_id,
                                           const int nstep);
  std::vector<CaptureSet> getCaptureRegion(const State state, const int nstep);

  bool capturable(State state, int nstep);
  bool capturable(int state_id, int nstep);

  int getMaxStep();

private:
  Grid         grid;
  Model        model;
  int         *data_basin;            // size = number of state
  CaptureSet **data_nstep;

  int state_num, input_num;
  int max_step;
};

} // namespace Capt

#endif // __CAPTURABILITY_H__