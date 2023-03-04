#ifndef ANT_ALGORITHM_COLONY_H_
#define ANT_ALGORITHM_COLONY_H_

#include "../../main_class/graph.h"
#include "../../helpers/s21_matrix.h"
#include "ant.h"

#include <random> 
#include <memory>

class Colony {
 public:
  Colony(Graph& graph);
  void findBestPath();

 private:
  const double kAlpha = 1;
  const double kBeta = 1;
  const double kDefaultPheromone = 1;
  const double kPheromoneEvaporation = 0.2;
  const double kPheromonePerAnt = 5;

  const int kRunsWithoutImprovement = 20;

  s21::Graph distances_;
  s21::Graph pheromones_;

  std::random_device rand_direction_;
  std::default_random_engine random_engine_;
  
  std::vector<std::unique_ptr<Ant>> ants_;
  void createAnts_();
}

#endif  // ANT_ALGORITHM_COLONY_H_