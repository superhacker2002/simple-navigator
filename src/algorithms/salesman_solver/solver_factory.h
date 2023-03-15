#ifndef SOLVER_FACTORY_H_
#define SOLVER_FACTORY_H_

#include <memory>
#include "solver_interface.h"

namespace SalesmanSolverFactory {
    enum struct SolverAlgorithm {
        ANT_COLONY_OPTIMIZATION = 0,
        BRANCH_AND_BOUND = 1
    };
    std::unique_ptr<ISalesmanSolver> getSalesmanSolver(SolverAlgorithm type, const s21::Graph& graph);
};

#endif  // SOLVER_FACTORY_H_  