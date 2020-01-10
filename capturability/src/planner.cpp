#include "planner.h"

using namespace Capt;

Planner::Planner(Model *model, Param *param, Config *config, Grid *grid, Capturability *capt){
  tree     = new Tree(grid, capt);
  search   = new Search(grid, tree);
  swing    = new Swing(model);
  pendulum = new Pendulum(model);

  model->read(&dt_min, "step_time_min");

  config->read(&dt, "timestep");
  config->read(&preview, "preview");
}

Planner::~Planner(){
  delete tree;
  delete search;
}

void Planner::set(EnhancedState state){
  this->state = state;
}

EnhancedInput Planner::get(){
  return this->input;
}

std::vector<Sequence> Planner::getSequence(){
  return search->getSequence();
}

arr3_t Planner::getFootstepR(){
  return search->getFootstepR();
}

arr3_t Planner::getFootstepL(){
  return search->getFootstepL();
}

bool Planner::plan(){
  rfoot = vec3Tovec2(state.rfoot);
  lfoot = vec3Tovec2(state.lfoot);
  icp   = vec3Tovec2(state.icp);
  if(state.elapsed < dt_min / 2) {
    elapsed = state.elapsed;
  }else{
    elapsed = dt_min / 2;
  }
  s_suf = state.s_suf;
  if(state.s_suf == FOOT_R) {
    suf = state.rfoot;
  }else{
    suf = state.lfoot;
  }

  calculateGoal();
  return runSearch();
}

void Planner::calculateStart(){

}

void Planner::calculateGoal(){
  double distMin       = 100; // set very large value as initial value
  int    currentFootId = 0;
  for(size_t i = 0; i < state.footstep.size(); i++) {
    if(state.footstep[i].suf == state.s_suf) {
      double dist = ( state.footstep[i].pos - suf ).norm();
      if(dist < distMin) {
        distMin       = dist;
        currentFootId = (int)i;
      }
    }
  }
  goal.clear();
  goal.resize(4);
  goal[0] = vec3Tovec2(state.footstep[currentFootId + 0].pos);
  goal[1] = vec3Tovec2(state.footstep[currentFootId + 1].pos);
  goal[2] = vec3Tovec2(state.footstep[currentFootId + 2].pos);
  goal[3] = vec3Tovec2(state.footstep[currentFootId + 3].pos);
}

bool Planner::runSearch(){
  search->setStart(rfoot, lfoot, icp, s_suf);
  search->setReference(goal);
  found = search->calc();

  if(found) { // if found solution
    // get state & input
    State s = search->getState();
    Input i = search->getInput();

    // calc swing foot trajectory
    swing->set(s.swf, i.swf, elapsed);

    // set to output
    input.duration = swing->getTime();
    input.suf      = suf;
    input.cop      = vec2Tovec3(i.cop);
    input.icp      = vec2Tovec3(s.icp);
    input.swf      = vec2Tovec3(s.swf);
    input.land     = vec2Tovec3(i.swf);
    printf("duration  %1.3lf\n", input.duration );
    printf("swf  %1.3lf, %1.3lf\n", input.swf.x(), input.swf.y() );
    printf("land %1.3lf, %1.3lf\n", input.land.x(), input.land.y() );

    return true;
  }else{ // couldn't found solution or reached goal
    return false;
  }
}

std::vector<CaptData> Planner::getCaptureRegion(){
  return search->getCaptureRegion();
}