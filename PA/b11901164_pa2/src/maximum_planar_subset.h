// **************************************************************************
//  File       [maximum_planar_subset.h]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The header file for the MaxPlanarSubset]
//  Date       2024/04/27
// **************************************************************************

#ifndef _MAXIMUM_PLANAR_SUBSET_H
#define _MAXIMUM_PLANAR_SUBSET_H

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class MPS_Tool {
public:
  MPS_Tool();  // constructor
  ~MPS_Tool(); // destructor
  vector<int> ConstructTable(vector<pair<int, int>> &data, int n);

private:
  void TraceBack(vector<pair<int, int>> &data, vector<vector<char>> &C, int i,
                 int j);
};

#endif
