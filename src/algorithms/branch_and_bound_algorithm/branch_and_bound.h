#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include "../../graph/graph.h"
#include "../../helpers/includes.h"

#include <vector>
#include <limits>

class BranchAndBound {
 public:
  BranchAndBound(const s21::Graph& graph);
  s21::TsmResult getShortestRoute();
  ~BranchAndBound();

 private:
  const double kMaxDistance = std::numeric_limits<double>::infinity(); 
  s21::Graph graph_;
  std::vector<bool> visited_;
  double final_res_;

  int firstMin_(int from);
  int secondMin_(int from);
  void TSPRec_(double curr_bound, double curr_weight, int level, std::vector<int>& curr_path);

};

#endif  // BRANCH_AND_BOUND_H_