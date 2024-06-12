// **************************************************************************
//  File       [cyclebreaker.h]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The header file of cyclebreaker of 2023 Spring Algorithm PA3]
//  Date       2024/06/12
// **************************************************************************

#ifndef CYCLEBREAKER_H
#define CYCLEBREAKER_H

#include <climits>
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

enum Color { WHITE, GRAY, BLACK };

typedef struct {
  uint16_t i, j;
  int w;
} Edge;

class Graph {
private:
  char type;
  uint16_t n;
  uint32_t m;
  int sum;                        // removed edge's weight sum
  vector<Edge> E;                 // edge vector (i, j, w)
  list<pair<uint16_t, int>> *adj; // adjacency list (j, w)
  bool DFS();
  bool detectCycle(uint16_t &u, uint8_t *color);

public:
  Graph(uint16_t &n, uint32_t &m, char &type);
  ~Graph();
  vector<Edge *> removedEdges;
  void addEdge(uint16_t &i, uint16_t &j, int &w);
  void mstKruskal(vector<Edge *> &E); // Maximum Spanning Tree by Kruskal's algo
  void breakDirectedGraphCycle(vector<Edge *> &E); // minimum cost forest by DFS
  void addRemovedEdgeWeight(int &w);
  int returnSum();
};

typedef struct {
  uint16_t p, rank;
} Vertex;

// ref: unit6b p.27-32
class DisjointSet {
private:
  uint16_t n;
  Vertex *V;

public:
  DisjointSet(uint16_t &n);
  ~DisjointSet();
  void makeSet();
  uint16_t findSet(uint16_t &i);
  void unionSets(uint16_t &i, uint16_t &j);
};

// ref: PA1
class SortTool {
private:
  void mergeSortSubVector(vector<Edge> &E, int low, int high);
  void merge(vector<Edge> &E, int low, int middle1, int middle2, int high);

public:
  SortTool();
  void mergeSort(vector<Edge> &E);
};

#endif
