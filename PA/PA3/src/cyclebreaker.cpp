// **************************************************************************
//  File       [cyclebreaker.cpp]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The body of cyclebreaker of 2023 Spring Algorithm PA3]
//  Date       2024/06/12
// **************************************************************************

#include "cyclebreaker.h"

// Graph class start
Graph::Graph(uint16_t &n, uint32_t &m, char &type)
    : n(n), m(m), type(type), sum(0) {
  if (type == 'd')
    adj = new list<pair<uint16_t, int>>[n];
  E.reserve(m);
}

Graph::~Graph() { delete[] adj; }

void Graph::addEdge(uint16_t &i, uint16_t &j, int &w) {
  if (type == 'd')
    adj[i].push_back(make_pair(j, w));
  E.push_back(Edge{i, j, w});
}

// ref: unit6b p.23 Kruskal's MST
// add edges in decreasing order => remove lightest edge that forms a cycle
void Graph::mstKruskal(vector<Edge *> &rmE) {
  DisjointSet A(n);
  SortTool ms;
  ms.mergeSort(E);
  // in order by decreasing weight
  for (int i = E.size() - 1; i >= 0; i--) {
    if (A.findSet(E[i].i) != A.findSet(E[i].j)) {
      A.unionSets(E[i].i, E[i].j);
    } else {
      rmE.push_back(&E[i]);
    }
  }
  /* debug */
  // for (int i = 0; i < rmEdges.size(); i++) {
  //   cout << "test: " << rmEdges[i]->i << " " << rmEdges[i]->j << " " <<
  //   rmEdges[i]->w << endl;
  // }
}

void Graph::breakDirectedGraphCycle(vector<Edge *> &rmE) {
  vector<Edge *> tempE;
  mstKruskal(tempE); // Maximum Spanning Tree

  // remove edges from adj in G
  for (uint32_t i = 0; i < tempE.size(); i++) {
    Edge e = *tempE[i];
    for (auto it = adj[e.i].begin(); it != adj[e.i].end(); it++) {
      if ((*it).first == e.j && (*it).second == e.w) {
        // cout << "test: " << e.i << " " << (*it).first << " " << (*it).second
        // << endl;
        adj[e.i].erase(it);
        break;
      }
    }
  }

  for (uint32_t i = 0; i < tempE.size(); i++) {
    if ((*tempE[i]).w <= 0) {
      rmE.push_back(tempE[i]);
      continue;
    }

    // add the edge back to the graph
    adj[(*tempE[i]).i].push_back(make_pair((*tempE[i]).j, (*tempE[i]).w));
    if (DFS()) {
      // remove the edge if it forms a cycle
      adj[(*tempE[i]).i].pop_back();
      rmE.push_back(tempE[i]);
    }
  }
}

// ref: unit6a p.24 DFS
bool Graph::DFS() {
  uint8_t *color = new uint8_t[n];
  for (uint16_t u = 0; u < n; u++) {
    color[u] = WHITE;
  }
  for (uint16_t u = 0; u < n; u++) {
    if (color[u] == WHITE) {
      if (detectCycle(u, color))
        return true;
    }
  }
  return false;
}

bool Graph::detectCycle(uint16_t &u, uint8_t *color) {
  color[u] = GRAY;
  for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
    uint16_t v = (*i).first;
    if (color[v] == WHITE) {
      if (detectCycle(v, color))
        return true;
    } else if (color[v] == GRAY) // back edge
      return true;               // cycle
  }
  color[u] = BLACK;
  return false;
}

void Graph::addRemovedEdgeWeight(int &w) { sum += w; }

int Graph::returnSum() { return sum; }

// Graph class end

// DisjointSet class start
DisjointSet::DisjointSet(uint16_t &n) : n(n) {
  V = new Vertex[n];
  makeSet();
}

DisjointSet::~DisjointSet() { delete[] V; }

// ref: unit6b p.31
void DisjointSet::makeSet() {
  for (int i = 0; i < n; i++) {
    V[i].p = i;
    V[i].rank = 0;
  }
}

uint16_t DisjointSet::findSet(uint16_t &i) {
  if (V[i].p != i)
    return findSet(V[i].p);
  return V[i].p;
}

void DisjointSet::unionSets(uint16_t &i, uint16_t &j) {
  uint16_t i_id = findSet(i);
  uint16_t j_id = findSet(j);
  // Link
  if (V[i_id].rank > V[j_id].rank)
    V[j_id].p = i_id;
  else {
    V[i_id].p = j_id;
    if (V[i_id].rank == V[j_id].rank)
      V[j_id].rank++;
  }
}
// DisjointSet class end

// SortTool class start
SortTool::SortTool() {}

void SortTool::mergeSort(vector<Edge> &data) {
  mergeSortSubVector(data, 0, data.size() - 1);
  // for (int i = 0; i < data.size(); i++) {
  //   cout << data[i].i << " " << data[i].j << " " << data[i].w << endl;
  // }
}

void SortTool::mergeSortSubVector(vector<Edge> &data, int low, int high) {
  if (low < high) {
    int middle1 = (low + high) / 2;
    int middle2 = middle1 + 1;
    mergeSortSubVector(data, low, middle1);
    mergeSortSubVector(data, middle2, high);
    merge(data, low, middle1, middle2, high);
  }
}

void SortTool::merge(vector<Edge> &data, int low, int middle1, int middle2,
                     int high) {
  int n1 = middle1 - low + 1;
  int n2 = high - middle2 + 1;
  vector<Edge> L(n1 + 1), R(n2 + 1);
  for (int i = 0; i < n1; i++) {
    L[i] = data[low + i];
  }
  for (int i = 0; i < n2; i++) {
    R[i] = data[middle2 + i];
  }
  L[n1].w = SHRT_MAX;
  R[n2].w = SHRT_MAX;
  int i = 0, j = 0;
  for (int k = low; k < high + 1; k++) {
    if (L[i].w <= R[j].w) {
      data[k] = L[i];
      i++;
    } else {
      data[k] = R[j];
      j++;
    }
  }
}

// SortTool class end
