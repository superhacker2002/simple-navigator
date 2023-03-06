#ifndef ANT_ALGORITHMS_SIMPLE_ACO_H_
#define ANT_ALGORITHMS_SIMPLE_ACO_H_

#include "../../main_class/graph.h"
#include "../../helpers/s21_matrix.h"
#include "constants.h"
#include <limits>
#include <vector>

class SimpleACO {
 public:
  SimpleACO(const s21::Graph& graph);
  TsmResult findBestPath();

 private:
  int cities_number_;
  int ants_number_;
  s21::Graph cities_;
  s21::Matrix<int> distances_;
  s21::Matrix<double> pheromones_;
  double best_path_;
  std::vector<AntType> ants_;
  int best_index_;

  std::vector<AntType> createAnts_();
  void restartAnts_();
  double antProduct_(int from, int to);
  int selectNextCity_(int ant);
  int simulateAnts_();
  void updateTrails_();
  void evaporatePheromones_();
  void addPheromones_();
};


#endif  // ANT_ALGORITHMS_SIMPLE_ACO_H_