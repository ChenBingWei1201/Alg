#include "maxPlanarSubset.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: ./mps <input file name> <output file name>\n";
    return 1;
  }

  std::ifstream inputFile(argv[1]);
  if (!inputFile) {
    std::cerr << "Error: Cannot open input file.\n";
    return 1;
  }

  int n, a, b;
  inputFile >> n;
  MaxPlanarSubset mps(n);

  while (inputFile >> a >> b && a != 0 && b != 0) {
    mps.addChord(a, b);
  }

  inputFile.close();

  int maxSubsetSize = mps.compute();
  auto subset = mps.getSubset();

  std::ofstream outputFile(argv[2]);
  if (!outputFile) {
    std::cerr << "Error: Cannot open output file.\n";
    return 1;
  }

  outputFile << maxSubsetSize << "\n";
  for (const auto &chord : subset) {
    outputFile << chord.first << " " << chord.second << "\n";
  }

  outputFile.close();
  return 0;
}
