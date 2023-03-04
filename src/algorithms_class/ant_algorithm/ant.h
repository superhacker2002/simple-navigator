#ifndef ANT_ALGORITHM_ANT_H_
#define ANT_ALGORITHM_ANT_H_

#include "../../main_class/graph.h"
#include "path.h"
#include <random>
#include <memory>

class Ant {
 public:
  Ant(std::default_random_engine &direction, int location, bool exact);
  int makeChoice(const s21::Graph& pheromone_, const s21::Graph distance, double alpha, double beta);
  int getLocation() const;
  std::unique_ptr<Path> getPath();
  bool canContinue() const;
  bool isOnStart() const;

 private:
  std::default_random_engine &random_engine;
  int location_;
  int start_;
  std::unique_ptr<Path> path_;
  bool canMove_;
}

#endif  // ANT_ALGORITHM_ANT_H_