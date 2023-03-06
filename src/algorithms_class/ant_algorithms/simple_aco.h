#ifndef ANT_ALGORITHMS_SIMPLE_ACO_H_
#define ANT_ALGORITHMS_SIMPLE_ACO_H_

#include "../../main_class/graph.h"
#include "../../helpers/s21_matrix.h"
#include "constants.h"

#include <limits>
#include <vector>
#include <random>

class SimpleACO {
 public:
  SimpleACO(const s21::Graph& graph);
  TsmResult findBestPath();

 private:
  int cities_number_;
  int ants_number_;
  double init_pheromone_;

  s21::Matrix<int> distances_;
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
  void logging();
};


#endif  // ANT_ALGORITHMS_SIMPLE_ACO_H_