#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "param.h"
#include "base.h"
#include "grid.h"
#include "node.h"
#include "capturability.h"
#include "grid_map.h"
#include "tree.h"
#include <vector>

namespace Capt {

#if 0
struct Trans {
  int                size;
  std::vector<State> states;
  std::vector<Input> inputs;

  void clear(){
    states.clear();
    inputs.clear();
  }
};

class Search {
public:
  Search(Grid *grid, Tree *tree);
  ~Search();

  void clear();

  // world frame coord.
  void setStart(vec3_t rfoot, vec3_t lfoot, vec3_t icp, Foot suf);
  void setReference(arr2_t posRef, arr2_t icpRef);

  bool calc(int preview);

  Trans getTrans();
  State getState();
  Input getInput();

  void                  calcSequence();
  std::vector<Sequence> getSequence();
  arr3_t                getFootstepR();
  arr3_t                getFootstepL();

  std::vector<CaptData> getCaptureRegion();

private:
  Grid *grid;
  Tree *tree;

  int max_step;

  // 現在の状態
  vec2_t rfoot, lfoot;

  Foot   s_suf, g_suf;
  State  s_state;
  int    s_state_id, s_input_id;
  arr2_t posRef, icpRef;          // ref

  Node *g_node;

  // 結果保存用変数
  std::vector<Sequence> seq;
  std::vector<CaptData> region;

  State ini_state;
  Input ini_input;
};
#endif

} // namespace Capt

#endif // __SEARCH_H__