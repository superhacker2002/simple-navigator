#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "../../../helpers/includes.h"

#include <limits>
#include <vector>

constexpr double kMaxDistance = s21::INF;
constexpr double kAlpha = 1.0; // weight of pheromones in path choice
constexpr double kBetha = 5.0; // weight of distance in path choice
constexpr double kEvaporationRate = 0.5;
constexpr double kConstQValue = 100.0;
constexpr int kMaxTours = 20; // max number of tours each ant can do
constexpr double kInitPheromone = 1.0 / 4.0;
constexpr int kUndefined = -1;
constexpr int kUnvisited = 0;
constexpr int kVisited = 1;

struct AntType {
  int cur_city, next_city, path_index;
  s21::VerticesList tabu;
  s21::VerticesList path;
  double tour_length;
};

#endif // CONSTANTS_H_