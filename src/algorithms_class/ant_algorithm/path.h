#ifndef ANT_ALGORITHM_PATH_H_
#define ANT_ALGORITHM_PATH_H_

#include <vector>
#include <ostream>

class Path {
 public:
  Path(int initial);
  double getDistance() const;
  int getNumberOfSteps() const;
  int operator[](int element) const;
  void addStep(int vertex, double dist);
  bool contains(int location);
  friend std::ostream& opertor<<(std::ostream& os, const Path& path);

 private:
  std::vetor<int> path_;
  double distance_;
}
#endif  // ANT_ALGORITHM_PATH_H_