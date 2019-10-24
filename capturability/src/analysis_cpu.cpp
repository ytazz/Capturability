#include "analysis_cpu.h"

namespace Capt {

Analysis::Analysis(Model model, Param param)
  : model(model), param(param), grid(param),
    num_state(grid.getNumState() ), num_input(grid.getNumInput() ), num_grid(grid.getNumGrid() ){
  printf("*** Analysis ***\n");
  printf("  Initializing ... ");
  fflush(stdout);
  initState();
  initInput();
  initTrans();
  initBasin();
  initNstep();
  initCop();
  initStepTime();

  setBasin();
  setCop();
  setStepTime();
  setTrans();
  printf("Done!\n");
}

Analysis::~Analysis() {
}

void Analysis::initState(){
  state = new State[num_state];
  for (int state_id = 0; state_id < num_state; state_id++)
    state[state_id] = grid.getState(state_id);
}

void Analysis::initInput(){
  input = new Input[num_input];
  for (int input_id = 0; input_id < num_input; input_id++)
    input[input_id] = grid.getInput(input_id);
}

void Analysis::initTrans(){
  trans = new int[num_grid];
  for (int id = 0; id < num_grid; id++)
    trans[id] = -1;
}

void Analysis::initBasin(){
  basin = new int[num_state];
  for (int state_id = 0; state_id < num_state; state_id++)
    basin[state_id] = -1;
}

void Analysis::initNstep(){
  nstep = new int[num_grid];
  for (int id = 0; id < num_grid; id++)
    nstep[id] = -1;
}

void Analysis::initCop(){
  cop = new Vector2[num_state];
  for (int state_id = 0; state_id < num_state; state_id++)
    cop[state_id].setCartesian(0.0, 0.0);
}

void Analysis::initStepTime(){
  step_time = new double[num_grid];
  for (int id = 0; id < num_grid; id++)
    step_time[id] = 0.0;
}

void Analysis::setBasin(){
  arr2_t foot_r;
  arr2_t foot_l;
  arr2_t region;
  foot_r = model.getVec("foot", "foot_r_convex");
  for(int state_id = 0; state_id < num_state; state_id++) {
    foot_l = model.getVec("foot", "foot_l_convex", state[state_id].swf);
    Polygon polygon;
    polygon.setVertex(foot_r);
    polygon.setVertex(foot_l);
    region = polygon.getConvexHull();
    if(polygon.inPolygon(state[state_id].icp, region) )
      basin[state_id] = 0;
  }
}

void Analysis::setCop(){
  Polygon polygon;
  arr2_t  region = model.getVec("foot", "foot_r_convex");
  for(int state_id = 0; state_id < num_state; state_id++)
    cop[state_id] = polygon.getClosestPoint(state[state_id].icp, region);
}

void Analysis::setStepTime(){
  SwingFoot swing_foot(model);

  for(int state_id = 0; state_id < num_state; state_id++) {
    for(int input_id = 0; input_id < num_input; input_id++) {
      int id = state_id * num_input + input_id;
      swing_foot.set(state[state_id].swf, input[input_id].swf);
      step_time[id] = swing_foot.getTime();
    }
  }
}

void Analysis::setTrans(){
  Pendulum pendulum(model);
  Vector2  icp;

  for(int state_id = 0; state_id < num_state; state_id++) {
    for(int input_id = 0; input_id < num_input; input_id++) {
      int id = state_id * num_input + input_id;

      pendulum.setIcp(state[state_id].icp);
      pendulum.setCop(cop[state_id]);
      icp = pendulum.getIcp(step_time[id]);

      State state_;
      state_.icp.setCartesian(-input[input_id].swf.x + icp.x, input[input_id].swf.y - icp.y);
      state_.swf.setCartesian(-input[input_id].swf.x, input[input_id].swf.y);

      trans[id] = grid.roundState(state_).id;
    }
  }
}

void Analysis::exe(const int n){
  printf("  Start %d-step analysis ... ", n);
  fflush(stdout);
  if(n > 0) {
    for(int state_id = 0; state_id < num_state; state_id++) {
      for(int input_id = 0; input_id < num_input; input_id++) {
        int id = state_id * num_input + input_id;
        if (trans[id] >= 0) {
          if (basin[trans[id]] == ( n - 1 ) ) {
            nstep[id] = n;
            if (basin[state_id] < 0) {
              basin[state_id] = n;
            }
          }
        }
      }
    }
  }
  printf("Done!\n");
}

void Analysis::saveCop(std::string file_name, bool header){
  FILE *fp = fopen(file_name.c_str(), "w");

  // Header
  if (header) {
    fprintf(fp, "%s,", "state_id");
    fprintf(fp, "%s,", "cop_x");
    fprintf(fp, "%s", "cop_y");
    fprintf(fp, "\n");
  }

  // Data
  for(int state_id = 0; state_id < num_state; state_id++) {
    fprintf(fp, "%d,", state_id);
    fprintf(fp, "%lf,", cop[state_id].x);
    fprintf(fp, "%lf", cop[state_id].y);
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void Analysis::saveStepTime(std::string file_name, bool header){
  FILE *fp = fopen(file_name.c_str(), "w");

  // Header
  if (header) {
    fprintf(fp, "%s,", "state_id");
    fprintf(fp, "%s,", "input_id");
    fprintf(fp, "%s", "step_time");
    fprintf(fp, "\n");
  }

  // Data
  for (int state_id = 0; state_id < num_state; state_id++) {
    for (int input_id = 0; input_id < num_input; input_id++) {
      int id = state_id * num_input + input_id;
      fprintf(fp, "%d,", state_id);
      fprintf(fp, "%d,", input_id);
      fprintf(fp, "%lf", step_time[id]);
      fprintf(fp, "\n");
    }
  }

  fclose(fp);
}

void Analysis::saveBasin(std::string file_name, bool header){
  FILE *fp = fopen(file_name.c_str(), "w");

  // Header
  if (header) {
    fprintf(fp, "%s,", "state_id");
    fprintf(fp, "%s", "nstep");
    fprintf(fp, "\n");
  }

  // Data
  for (int state_id = 0; state_id < num_state; state_id++) {
    fprintf(fp, "%d,", state_id);
    fprintf(fp, "%d", basin[state_id]);
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void Analysis::saveNstep(std::string file_name, bool header){
  FILE *fp  = fopen(file_name.c_str(), "w");
  int   max = 0;

  // Header
  if (header) {
    fprintf(fp, "%s,", "state_id");
    fprintf(fp, "%s,", "input_id");
    fprintf(fp, "%s,", "trans");
    fprintf(fp, "%s", "nstep");
    fprintf(fp, "\n");
  }

  // Data
  int num_step[NUM_STEP_MAX + 1];
  for(int i = 0; i < NUM_STEP_MAX + 1; i++) {
    num_step[i] = 0;
  }
  for (int state_id = 0; state_id < num_state; state_id++) {
    for (int input_id = 0; input_id < num_input; input_id++) {
      int id = state_id * num_input + input_id;
      fprintf(fp, "%d,", state_id);
      fprintf(fp, "%d,", input_id);
      fprintf(fp, "%d,", trans[id]);
      fprintf(fp, "%d", nstep[id]);
      fprintf(fp, "\n");

      if (max < nstep[id])
        max = nstep[id];
      if(nstep[id] > 0)
        num_step[nstep[id]]++;
    }
  }

  printf("*** Result ***\n");
  printf("  max(nstep) = %d\n", max);
  for(int i = 1; i <= max; i++) {
    printf("  %d-step capture point: %d\n", i, num_step[i]);
  }

  fclose(fp);
}

} // namespace Capt