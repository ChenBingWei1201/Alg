// **************************************************************************
//  File       [maximum_planar_subset.cpp]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The header file for the MaxPlanarSubset]
//  Date       2024/04/27
// **************************************************************************

#include "maximum_planar_subset.h"

using namespace std;

// Constructor
MPS_Tool::MPS_Tool() {}

// Destructor
MPS_Tool::~MPS_Tool() {}

vector<int> MPS_Tool::FindPair(vector<pair<int, int>> &data, int n) {
  vector<vector<unsigned short>> M(n, vector<unsigned short>(n, 0));
  vector<vector<char>> S(n, vector<char>(n, 1));

  for (int d = 1; d < n; d++) {
    for (int i = 0; i < n - d; i++) {
      int j = i + d;
      int k = data[j].second;
      if (k == i) {
        M[i][j] = M[i + 1][j - 1] + 1;
        S[i][j] = 2;
      } else if (k > i && k <= j) {
        int temp = M[i][k - 1] + 1 + M[k + 1][j - 1];
        if (M[i][j - 1] <= temp) {
          M[i][j] = temp;
          S[i][j] = 3;
        } else {
          M[i][j] = M[i][j - 1];
        }
      } else {
        M[i][j] = M[i][j - 1];
      }
    }
  }

  vector<int> result;
  result.reserve(n); // reserve memory
  result.push_back(M[0][n - 1]);
  FindChord(data, result, S, 0, n - 1);
  return result;
}

void MPS_Tool::FindChord(vector<pair<int, int>> &data, vector<int> &result,
                         vector<vector<char>> &S, int i, int j) {
  while (S[i][j] == 1 && j > 0) {
    --j;
  }
  if (i >= S.size() || j <= 0) {
    return;
  }
  unsigned short temp = j;
  if (S[i][j] == 2) {
    result.push_back(temp);
    FindChord(data, result, S, i + 1, j - 1);
  } else if (S[i][j] == 3) {
    result.push_back(temp);
    FindChord(data, result, S, i, data[j].second - 1);
    FindChord(data, result, S, data[j].second + 1, j - 1);
  }
}
