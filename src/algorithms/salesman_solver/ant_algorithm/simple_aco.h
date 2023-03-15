#ifndef SIMPLE_ACO_H_
#define SIMPLE_ACO_H_

#include "../../../helpers/s21_matrix.h"
#include "../../../helpers/includes.h"
#include "../../../graph/graph.h"
#include "constants.h"
#include "../solver_interface.h"

#include <limits>
#include <random>
#include <vector>

class SimpleACO : public ISalesmanSolver {
 public:
  SimpleACO(const s21::Graph& graph);
  s21::TsmResult findBestPath() override;

 private:
  int cities_number_;
  int ants_number_;
  double init_pheromone_;

  s21::Matrix<double> distances_;
  s21::Matrix<double> pheromones_;

  double best_path_length_;
  std::vector<int> best_path_;

  std::vector<AntType> ants_;

  std::random_device rand_dev_;
  std::default_random_engine random_generator_;

  std::vector<AntType> createAnts_();
  void restartAnts_();
  double antProduct_(int from, int to);
  int selectNextCity_(int ant);
  int simulateAnts_();
  void updateTrails_();
  void evaporatePheromones_();
  void addPheromones_();
};

#endif  // SIMPLE_ACO_H_