// **************************************************************************
//  File       [maximum_planar_subset.cpp]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The body of MaxPlanarSubset]
//  Date       2024/04/27
// **************************************************************************

#include "maximum_planar_subset.h"

using namespace std;

// Constructor
MPS_Tool::MPS_Tool() {}

// Destructor
MPS_Tool::~MPS_Tool() {}
vector<int> output;

vector<int> MPS_Tool::ConstructTable(vector<pair<int, int>> &data, int n) {
  vector<vector<unsigned short>> M(n, vector<unsigned short>(n, 0));
  vector<vector<char>> C(n, vector<char>(n, 1));

  // d represents the difference between the indices i and j
  // below code iterates over all pairs of indices (i, j) where j > i
  // k is the endpoint of the chord starting at point j
  for (int d = 1; d < n; d++) {
    for (int i = 0; i < n - d; i++) {
      int j = i + d;
      int k = data[j].second;
      if (k == i) { // chord (i, j) is a part of the maximum planar subset
        M[i][j] = M[i + 1][j - 1] + 1;
        C[i][j] = 3;
      } else if (k > i && k <= j) {
        // chord (i, j) intersects with some other chord
        int temp = M[i][k - 1] + 1 + M[k + 1][j - 1];
        if (M[i][j - 1] <= temp) {
          M[i][j] = temp;
          C[i][j] = 2;
        } else {
          M[i][j] = M[i][j - 1];
        }
      } else { // chord (i, j) does not intersect with any other chord
        M[i][j] = M[i][j - 1];
      }
    }
  }

  output.reserve(n); // reserve memory
  output.push_back(M[0][n - 1]);
  TraceBack(data, C, 0, n - 1);
  return output;
}

void MPS_Tool::TraceBack(vector<pair<int, int>> &data, vector<vector<char>> &C,
                         int i, int j) {
  while (C[i][j] == 1 && j > 0) {
    --j;
  }
  if (i >= C.size() || j <= 0) {
    return;
  }
  if (C[i][j] == 2) {
    output.push_back(j);
    TraceBack(data, C, i, data[j].second - 1);
    TraceBack(data, C, data[j].second + 1, j - 1);
  } else if (C[i][j] == 3) {
    output.push_back(j);
    TraceBack(data, C, i + 1, j - 1);
  }
}
