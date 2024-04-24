#ifndef MAX_PLANAR_SUBSET_H
#define MAX_PLANAR_SUBSET_H

#include <utility>
#include <vector>

class MaxPlanarSubset {
public:
  explicit MaxPlanarSubset(int totalVertices);
  void addChord(int a, int b);
  int compute();
  std::vector<std::pair<int, int>> getSubset();

private:
  std::vector<std::pair<int, int>> chords;
  std::vector<std::vector<int>> dp;
  std::vector<std::vector<int>> next;
  int totalVertices;

  void initialize();
  void computeDpAndNext();
  void traceBackSubset(int i, int j, std::vector<std::pair<int, int>> &subset);
};

#endif // MAX_PLANAR_SUBSET_H
