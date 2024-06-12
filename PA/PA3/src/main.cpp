// **************************************************************************
//  File       [main.cpp]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The main program of 2023 Spring Algorithm PA3]
//  Date       2024/06/12
// **************************************************************************

#include "../lib/tm_usage.h"
#include "cyclebreaker.h"
#include <fstream>
#include <iostream>

using namespace std;

void help_message() {
  cout << "usage: ./bin/cb <input_file> <output_file> " << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    help_message();
    return 0;
  }
  CommonNs::TmUsage tmusg;
  CommonNs::TmStat stat;

  fstream fin(argv[1]);
  fstream fout;
  fout.open(argv[2], ios::out);

  char type;     // u: undirected graph, d: directed graph
  uint16_t n;    // number of vertices (1 ≤ n ≤ 10000)
  uint32_t m;    // number of edges (1 ≤ m ≤ 50000000)
  uint16_t i, j; // edge from i to j (0 ≤ i, j ≤ n-1)
  int w;         // weight w (-100 <= w <= 100)
  fin >> type >> n >> m;

  Graph *G;
  G = new Graph(n, m, type);
  for (uint32_t k = 0; k < m; k++) {
    fin >> i >> j >> w;
    G->addEdge(i, j, w);
  }
  fin.close();

  tmusg.periodStart();
  if (type == 'd') {
    G->breakDirectedGraphCycle(G->removedEdges);
  } else {
    G->mstKruskal(G->removedEdges);
  }
  for (uint32_t i = 0; i < G->removedEdges.size(); i++) {
    G->addRemovedEdgeWeight(G->removedEdges[i]->w);
  }
  tmusg.getPeriodUsage(stat);
  cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms"
       << endl;
  cout << "memory: " << stat.vmPeak << "KB" << endl;

  if (G->removedEdges.empty()) {
    fout << '0' << endl;
  } else {
    fout << G->returnSum() << endl;
    for (uint32_t i = 0; i < G->removedEdges.size(); i++) {
      fout << G->removedEdges[i]->i << " " << G->removedEdges[i]->j << " "
           << G->removedEdges[i]->w << endl;
    }
  }
  fout.flush();
  fout.close();
  delete G;
  return 0;
}
