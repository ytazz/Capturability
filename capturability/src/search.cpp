#include "search.h"

namespace Capt {

Search::Search(Grid *grid, Tree *tree) :
  grid(grid), tree(tree){
}

Search::~Search() {
}

void Search::clear(){
  seq.clear();
  region.clear();
}

void Search::setStart(vec2_t rfoot, vec2_t lfoot, vec2_t icp, double elapsed, Foot suf){
  this->rfoot = rfoot;
  this->lfoot = lfoot;
  this->s_suf = suf;

  // round to support foot coord.
  if(s_suf == FOOT_R) {
    s_lfoot.x() = +( lfoot.x() - rfoot.x() );
    s_lfoot.y() = +( lfoot.y() - rfoot.y() );
    s_icp.x()   = +( icp.x() - rfoot.x() );
    s_icp.y()   = +( icp.y() - rfoot.y() );
    s_elapsed   = elapsed;
    s_state.icp = s_icp;
    s_state.swf = s_lfoot;
  }else{
    s_rfoot.x() = +( rfoot.x() - lfoot.x() );
    s_rfoot.y() = -( rfoot.y() - lfoot.y() );
    s_icp.x()   = +( icp.x() - lfoot.x() );
    s_icp.y()   = -( icp.y() - lfoot.y() );
    s_elapsed   = elapsed;
    s_state.icp = s_icp;
    s_state.swf = s_rfoot;
  }
  s_state    = grid->roundState(s_state).state;
  s_state_id = grid->roundState(s_state).id;
}

void Search::setReference(arr2_t foot){
  ref.resize(foot.size() );

  for(size_t i = 0; i < foot.size(); i++) {
    if(s_suf == FOOT_R) {
      ref[i].x() = +( foot[i].x() - rfoot.x() );
      ref[i].y() = +( foot[i].y() - rfoot.y() );
    }else{
      ref[i].x() = +( foot[i].x() - lfoot.x() );
      ref[i].y() = -( foot[i].y() - lfoot.y() );
    }
  }

  // g_foot.x() = round(g_foot.x() / 0.05) * 0.05;
  // g_foot.y() = round(g_foot.y() / 0.05) * 0.05;
}

bool Search::calc(int preview){
  tree->clear();
  seq.clear();
  region.clear();
  g_node = tree->search(s_state_id, s_suf, ref, preview);
  if(g_node == NULL) {
    return false;
  }else{
    calcSequence();
    if(s_suf == FOOT_R) {
      region = tree->getCaptureRegion(s_state_id, s_input_id, s_suf, rfoot);
    }else{
      region = tree->getCaptureRegion(s_state_id, s_input_id, s_suf, lfoot);
    }
    return true;
  }
}

Trans Search::getTrans(){
  Trans trans;

  std::vector<int> input_ids;
  Node            *node = g_node;
  while(node != NULL) {
    trans.states.push_back(grid->getState(node->state_id) );
    trans.inputs.push_back(grid->getInput(node->input_id) );
    input_ids.push_back(node->input_id);

    node = node->parent;
  }
  trans.inputs.pop_back();
  input_ids.pop_back();

  std::reverse(trans.states.begin(), trans.states.end() );
  std::reverse(trans.inputs.begin(), trans.inputs.end() );
  std::reverse(input_ids.begin(), input_ids.end() );

  s_input_id = input_ids[0];

  return trans;
}

State Search::getState(){
  return ini_state;
}

Input Search::getInput(){
  return ini_input;
}

void Search::calcSequence(){
  Trans trans = getTrans();

  vec2_t   suf_pos(0, 0);
  vec2_t   swf_pos(0, 0);
  vec2_t   icp_pos(0, 0);
  vec2_t   cop_pos(0, 0);
  Sequence seq_;

  int amari;
  if(s_suf == Foot::FOOT_R) {
    amari   = 0;
    suf_pos = rfoot;
  }else{
    amari   = 1;
    suf_pos = lfoot;
  }

  for(size_t i = 0; i < trans.states.size(); i++) { // right support
    if( ( (int)i % 2 ) == amari) {
      icp_pos = suf_pos + trans.states[i].icp;
      if(i < trans.inputs.size() ) {
        cop_pos = suf_pos + trans.inputs[i].cop;
      }
      seq_.substitute(Foot::FOOT_R, suf_pos, icp_pos, cop_pos);

      if(i == 0) {
        ini_state.icp = suf_pos + trans.states[0].icp;
        ini_state.swf = suf_pos + trans.states[0].swf;
        ini_state.elp = trans.states[0].elp;
        ini_input.cop = suf_pos + trans.inputs[0].cop;
        ini_input.swf = suf_pos + trans.inputs[0].swf;
      }

      suf_pos = suf_pos + trans.inputs[i].swf;
    }else{ // left support
      icp_pos = suf_pos + mirror(trans.states[i].icp);
      if(i < trans.inputs.size() ) {
        cop_pos = suf_pos + mirror(trans.inputs[i].cop );
      }
      seq_.substitute(Foot::FOOT_L, suf_pos, icp_pos, cop_pos);

      if(i == 0) {
        ini_state.icp = suf_pos + mirror(trans.states[0].icp);
        ini_state.swf = suf_pos + mirror(trans.states[0].swf);
        ini_state.elp = trans.states[0].elp;
        ini_input.cop = suf_pos + mirror(trans.inputs[0].cop);
        ini_input.swf = suf_pos + mirror(trans.inputs[0].swf);
      }

      suf_pos = suf_pos + mirror(trans.inputs[i].swf);
    }
    seq.push_back(seq_);
  }
  // seq.erase(seq.begin() );
}

std::vector<Sequence> Search::getSequence(){
  return seq;
}

arr3_t Search::getFootstepR(){
  arr3_t footstep_r;
  for(size_t i = 0; i < seq.size(); i++) {
    if(seq[i].suf == Foot::FOOT_R) {
      footstep_r.push_back(seq[i].pos);
    }
  }
  return footstep_r;
}

arr3_t Search::getFootstepL(){
  arr3_t footstep_l;
  for(size_t i = 0; i < seq.size(); i++) {
    if(seq[i].suf == Foot::FOOT_L) {
      footstep_l.push_back(seq[i].pos);
    }
  }
  return footstep_l;
}

std::vector<CaptData> Search::getCaptureRegion(){
  return region;
}

} // namespace Capt