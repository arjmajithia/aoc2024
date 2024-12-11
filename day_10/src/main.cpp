#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day10_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day10_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<int>> map;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<int> ln;
      for (char c : line) {
        if (isdigit(c)) { ln.push_back(c - '0'); }
      }
      map.push_back(ln);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  std::pair<int, int> dimensions = {map.size(), map[0].size()};

  std::vector<std::pair<int, int>> zero_locs;
  for (int row = 0; row < map.size(); row++) {
    for (int col = 0; col < map[row].size(); col++) {
      if (map[row][col] == 0) { zero_locs.push_back({row, col}); }
    }
  }
  
  for (auto v : map) {
    for (auto c : v) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  int total = 0;

  for (auto location : zero_locs) {
    total += p2_::walk(map, dimensions, location);
  }

  std::cout << total << std::endl;
  return 0;
}

int p1() {
  /* std::string filename = "inputs/day10_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day10_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<int>> map;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<int> ln;
      for (char c : line) {
        if (isdigit(c)) { ln.push_back(c - '0'); }
      }
      map.push_back(ln);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  std::pair<int, int> dimensions = {map.size(), map[0].size()};

  std::vector<std::pair<int, int>> zero_locs;
  for (int row = 0; row < map.size(); row++) {
    for (int col = 0; col < map[row].size(); col++) {
      if (map[row][col] == 0) { zero_locs.push_back({row, col}); }
    }
  }
  
  for (auto v : map) {
    for (auto c : v) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  int total = 0;
  for (auto location : zero_locs) {
    std::set<std::pair<int, int>> visited;
    p1_::walk(map, dimensions, location, visited);
    total += visited.size();
  }

  std::cout << total << std::endl;
  return 0;
}

int main() {
#ifdef PART1
  p1();
#endif
#ifndef PART1
  p2();
#endif
}
