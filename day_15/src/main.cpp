#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

std::map<char, std::pair<int, int>> c_direction = {
  {'^', {-1, 0}},
  {'>', {0, 1}},
  {'v', {1, 0}},
  {'<', {0, -1}}
};

bool isvalid(std::pair<int, int> c_l, std::pair<int, int> m_b) {
  return 
    c_l.first < m_b.first &&
    c_l.first > 0 &&
    c_l.second < m_b.second &&
    c_l.second > 0;
}

int p2() {
  return 0;
}

int p1() {
  /* std::string filename = "inputs/day15_1.txt"; */
  std::string filename = "inputs/tmp";
  /* std::string filename = "inputs/day15_1.prod"; */
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  bool reading_map = true;

  std::vector<std::pair<int, int>> movements;
  std::vector<std::vector<char>> c_map;
  std::vector<std::vector<int>> map;
  std::pair<int, int> current_location;

  int row = 0;
  int col = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> ln_map;
      if(line.find_first_not_of(' ') != std::string::npos)
      {
        if (reading_map) { 
          std::vector<int> inv_map;
          for (int col = 0; col < line.length(); ++col) {
            char c = line[col];
            ln_map.push_back(c);
            if (c == '#') { inv_map.push_back(-1); }
            else if (c == 'O') { inv_map.push_back(1); }
            else if (c == '@') { inv_map.push_back(2); current_location = std::make_pair(row, col); }
            else { inv_map.push_back(0); }
          }
          map.push_back(inv_map);
        }
        else {
          for (int i = 0; i < line.length(); ++i) {
            movements.push_back(c_direction[line[i]]);
          }
        }
      }
      else { reading_map = false; }
      row++;
      col = line.length();
      c_map.push_back(ln_map);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  std::pair<int, int> map_bounds = std::make_pair(row, col);
  for (auto r : c_map) {
    for (auto c : r) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  /* for (auto r : map) { */
  /*   for (auto c : r) { */
  /*     std::cout << c; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */

  std::vector<std::tuple<int, int, int>> changed;
  for (int i = 0; i < movements.size(); ++i) {
    std::cout << "Moving: " << movements[i].first << ", " << movements[i].second << " | ";
    int previous = map[current_location.first][current_location.second];
    if (p1_::check_push(current_location, movements[i], map_bounds, map, changed, previous)) {
      std::cout << "true" << std::endl;

      for (auto c : changed) {
        map[std::get<0>(c)][std::get<1>(c)] = std::get<2>(c);
      }

      map[current_location.first][current_location.second] = 0;

      current_location = {
        current_location.first + movements[i].first, 
        current_location.second + movements[i].second};


      for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
          if (map[i][j] == 1) { std::cout << "O"; }
          if (map[i][j] == 2) { std::cout << "@"; }
          if (map[i][j] == 0) { std::cout << "."; }
          if (map[i][j] == -1) { std::cout << "#"; }
        }
        std::cout << std::endl;
      }
      changed.clear();
    }
    else {
      std::cout << "false" << std::endl;
    }
    /* if (!isvalid(ch_l, map_bounds)) { continue; } */
  
    /* current_location = ch_l; */
  }
  std::cout << current_location.first << ", " << current_location.second << std::endl;

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
