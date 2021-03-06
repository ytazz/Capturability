#include "model.h"
#include "param.h"
#include "config.h"
#include "grid.h"
#include "grid_map.h"
#include "timer.h"
#include "tree.h"
#include "search.h"
#include "step_plot.h"
#include "monitor.h"
#include "planner.h"
#include <chrono>

using namespace std;
using namespace Capt;

int main(int argc, char const *argv[]) {
  Model *model = new Model("data/valkyrie.xml");
  Param *param = new Param("data/valkyrie_xy.xml");
  Grid  *grid  = new Grid(param);

  // capturability
  Capturability *capturability = new Capturability(grid);
  capturability->loadBasin("cpu/Basin.csv");
  capturability->loadNstep("cpu/Nstep.csv");

  Monitor  *monitor  = new Monitor(model, grid, capturability);
  Pendulum *pendulum = new Pendulum(model);
  Swing    *swing    = new Swing(model);

  // footstep
  Step step[11];
  step[0].pos  = vec3_t(0.00, -0.20, 0);
  step[0].suf  = Foot::FOOT_R;
  step[1].pos  = vec3_t(0.05, +0.25, 0);
  step[1].suf  = Foot::FOOT_L;
  step[2].pos  = vec3_t(0.25, +0.05, 0);
  step[2].suf  = Foot::FOOT_R;
  step[3].pos  = vec3_t(0.45, +0.25, 0);
  step[3].suf  = Foot::FOOT_L;
  step[4].pos  = vec3_t(0.65, +0.05, 0);
  step[4].suf  = Foot::FOOT_R;
  step[5].pos  = vec3_t(0.85, +0.25, 0);
  step[5].suf  = Foot::FOOT_L;
  step[6].pos  = vec3_t(1.15, +0.05, 0);
  step[6].suf  = Foot::FOOT_R;
  step[7].pos  = vec3_t(1.45, +0.25, 0);
  step[7].suf  = Foot::FOOT_L;
  step[8].pos  = vec3_t(1.75, +0.05, 0);
  step[8].suf  = Foot::FOOT_R;
  step[9].pos  = vec3_t(2.05, +0.25, 0);
  step[9].suf  = Foot::FOOT_L;
  step[10].pos = vec3_t(2.00, -0.20, 0);
  step[10].suf = Foot::FOOT_R;
  Footstep footstep;
  for(int i = 0; i <= 10; i++) {
    footstep.push_back(step[i]);
  }

  EnhancedState state;
  state.footstep = footstep;
  state.rfoot    = vec3_t(0, -0.2, 0);
  state.lfoot    = vec3_t(0, +0.2, 0);
  state.icp      = vec3_t(0, 0, 0);
  state.elapsed  = 0.0;
  state.s_suf    = Foot::FOOT_R;

  EnhancedInput input;
  for(int i = 0; i <= 3; i++) {
    StepPlot *plt = new StepPlot(model, param, grid);

    bool safe = monitor->check(state, footstep );
    printf("safe: %d\n", safe);

    // draw path
    input = monitor->get();
    pendulum->setIcp(input.icp);
    pendulum->setCop(input.cop);
    vec2_t icp_hat = pendulum->getIcp(0.05);
    plt->setFootR(vec3Tovec2(input.suf) );
    plt->setFootL(vec3Tovec2(input.land) );
    plt->setCop(vec3Tovec2(input.cop) );
    plt->setIcp(vec3Tovec2(input.icp) );
    plt->setIcp(icp_hat);
    swing->set(input.swf, input.land, state.elapsed);
    vec3_t swf = swing->getTraj(state.elapsed + 0.05);
    printf("icp_hat %1.3lf, %1.3lf\n", icp_hat.x(), icp_hat.y() );
    printf("swf     %1.3lf, %1.3lf, %1.3lf\n", swf.x(), swf.y(), swf.z() );
    plt->setFootL(vec3Tovec2(swf) );

    plt->plot();

    state.rfoot    = vec3_t(0, -0.2, 0);
    state.lfoot    = swf;
    state.icp      = vec2Tovec3(icp_hat);
    state.elapsed += 0.05;

    delete plt;
  }

  return 0;
}