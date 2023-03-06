#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <limits>
#include <vector>

constexpr int kCitiesNumber = 30;
constexpr int kAntsNumber = 30;
constexpr double kMaxDistance = std::numeric_limits<double>::infinity();
constexpr double kAlpha = 1.0;  // weight of pheromones in path choice
constexpr double kBetha = 1.0;  // weight of distance in path choice
constexpr double kEvaporationRate = 0.5;
constexpr double kConstQValue = 100.0;

// ?
constexpr int kMaxTours = 20;
constexpr int kMaxTime = kMaxTours * kCitiesNumber;
constexpr double kInitPheromone =  1.0 / kCitiesNumber;

struct AntType {
    int cur_city, next_city, path_index;
    std::vector<int> tabu;
    std::vector<int> path;
    double tour_length;
};

struct TsmResult {
    std::vector<int> vertices;
    double distance;
};

#endif  // CONSTANTS_H_