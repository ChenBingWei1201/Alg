// **************************************************************************
//  File       [main.cpp]
//  Author     [Bing-Wei Chen]
//  Synopsis   [The main program of 2023 Spring Algorithm PA2]
//  Date       2024/04/27
// **************************************************************************

#include "../lib/tm_usage.h"
#include "maximum_planar_subset.h"
#include <algorithm> // std::sort
#include <fstream>
#include <iostream>
#include <utility> // std::pair

using namespace std;

void help_message() {
  cout << "usage: ./bin/mps <input_file> <output_file>" << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    help_message();
    return 0;
  }
  CommonNs::TmUsage tmusg;
  CommonNs::TmStat stat;

  //////////// read the input file /////////////
  fstream fin(argv[1]);
  fstream fout;
  fout.open(argv[2], ios::out);

  int n;
  int start, end, junk;
  fin >> n; // n = 2N - 1

  // store the input data as vector and pairs
  vector<pair<int, int>> data(n);
  for (int i = 0; i < n / 2; i++) {
    fin >> start >> end;
    data[start] = make_pair(start, end);
    data[end] = make_pair(end, start);
  }
  fin >> junk;

  //////////// the algorithm part ////////////////
  tmusg.periodStart();
  MPS_Tool mps;
  vector<int> output = mps.ConstructTable(data, n); // Construct tables for dp
  tmusg.getPeriodUsage(stat);
  cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms"
       << endl;
  cout << "memory: " << stat.vmPeak << "KB" << endl;

  //////////// write the output file ///////////
  int result = output.front();
  output.erase(output.begin()); // delete the first element
  for (int i = 0; i < output.size(); i++) {
    output[i] = data[output[i]].second;
  }
  sort(output.begin(), output.begin() + result); // sort by the first element

  fout << result << endl;

  for (int i = 0; i < output.size(); i++) {
    fout << output[i] << " " << data[output[i]].second << endl;
  }
  fin.close();
  fout.close();
  return 0;
}
