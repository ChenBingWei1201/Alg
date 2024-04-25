#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<int> findPair(vector<pair<int, int>> &data, int n);
void findChord(vector<pair<int, int>> &data, vector<int> &result,
               vector<vector<char>> &s, int i, int j);
