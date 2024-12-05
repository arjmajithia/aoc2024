#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day4_2.txt"; */
  std::string filename = "inputs/day4_2.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<char>> search_map;

  int line_num = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> line_(line.begin(), line.end());
      search_map.push_back(line_);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<std::pair<int, int>> valids;

  for (int row = 0; row < search_map.size(); ++row) {
    std::vector<char> v = search_map[row];
    for (int col = 0; col < v.size(); ++col) {
      char c = v[col];
      if (c == 'A') {
        if (p2_::on_A({ row, col }, search_map)) {
          valids.push_back({row, col});
        }
      } 
    }
  }

  /* for (auto p : valids) { */
  /*   std::cout << p.first << " , " << p.second << std::endl; */
  /* } */
  std::cout << valids.size() << std::endl;
  return 0;
}

int p1() {
  /* std::string filename = "inputs/day4_1.txt"; */
  std::string filename = "inputs/day4_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<char>> search_map;

  int line_num = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> line_(line.begin(), line.end());
      search_map.push_back(line_);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<std::pair<int, int>> valids;

  for (int row = 0; row < search_map.size(); ++row) {
    std::vector<char> v = search_map[row];
    for (int col = 0; col < v.size(); ++col) {
      char c = v[col];
      if (c == 'X') {
        auto directions = p1_::get_valid_directions({ row, col }, { search_map.size(), v.size() });
        for (auto direction : directions) {
          if (p1_::check_X(direction, search_map, { row , col })) {
            valids.push_back({row, col});
          }
        }
      } 
    }
  }

  /* for (auto p : valids) { */
  /*   std::cout << p.first << " , " << p.second << std::endl; */
  /* } */
  std::cout << valids.size() << std::endl;
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
