#ifndef SOLVER_INTERFACE_H_
#define SOLVER_INTERFACE_H_

#include "../../graph/graph.h"

class ISalesmanSolver {
public:
  virtual ~ISalesmanSolver() = default;
  virtual s21::TsmResult findBestPath() = 0;
};

#endif // SOLVER_INTERFACE_H_