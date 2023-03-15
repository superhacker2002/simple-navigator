#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include <limits>
#include <vector>

#include "../../../graph/graph.h"
#include "../../../helpers/includes.h"
#include "../solver_interface.h"

class BranchAndBound : public ISalesmanSolver {
 public:
  BranchAndBound(const s21::Graph& graph);
  s21::TsmResult findBestPath() override;
  ~BranchAndBound();

 private:
  const double kMaxDistance = std::numeric_limits<double>::infinity();
  s21::Graph graph_;
  std::vector<bool> visited_;
  double final_res_;
  std::vector<int> final_path_;

  int firstMin_(int from);
  int secondMin_(int from);
  void TSPRec_(double curr_bound, double curr_weight, int level,
               std::vector<int>& curr_path);
  void setLastStep_(double curr_weight, int level, std::vector<int>& curr_path);
  void calculateCurrentBound_(int level, double& curr_bound,
                      std::vector<int>& curr_path, int vertice);
  double calculateInitBound_();
  void resetVisitedVertices_(std::vector<int>&curr_path, int level);
  void convertPath_();
};

#endif  // BRANCH_AND_BOUND_H_