#include "maxPlanarSubset.h"
#include <algorithm>

MaxPlanarSubset::MaxPlanarSubset(int totalVertices)
: totalVertices(totalVertices), dp(totalVertices, std::vector<int>(totalVertices, 0)),
  next(totalVertices, std::vector<int>(totalVertices, -1)) {}

void MaxPlanarSubset::addChord(int a, int b) {
    if (a > b) std::swap(a, b);
    chords.emplace_back(a, b);
}

void MaxPlanarSubset::initialize() {
    std::sort(chords.begin(), chords.end());
    for (auto &chord : chords) {
        next[chord.first][chord.second] = chord.second;
    }
}

void MaxPlanarSubset::computeDpAndNext() {
    for (int length = 2; length < totalVertices; length++) {
        for (int i = 0; i + length < totalVertices; i++) {
            int j = i + length;
            dp[i][j] = dp[i][j - 1];
            if (next[i][j] != -1) {
                int k = next[i][j];
                dp[i][j] = std::max(dp[i][j], 1 + dp[i][k - 1] + dp[k + 1][j]);
            }
            for (int k = i; k < j; k++) {
                if (next[i][k] != -1 && k + 1 < j) {
                    dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
}

int MaxPlanarSubset::compute() {
    initialize();
    computeDpAndNext();
    return dp[0][totalVertices - 1];
}

std::vector<std::pair<int, int>> MaxPlanarSubset::getSubset() {
    std::vector<std::pair<int, int>> subset;
    traceBackSubset(0, totalVertices - 1, subset);
    return subset;
}

void MaxPlanarSubset::traceBackSubset(int i, int j, std::vector<std::pair<int, int>>& subset) {
    if (i >= j) return;
    if (next[i][j] != -1 && dp[i][j] == 1 + dp[i][next[i][j] - 1] + dp[next[i][j] + 1][j]) {
        subset.emplace_back(i, next[i][j]);
        traceBackSubset(i, next[i][j] - 1, subset);
        traceBackSubset(next[i][j] + 1, j, subset);
    } else {
        traceBackSubset(i, j - 1, subset);
    }
}
