#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day6_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day6_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<char>> map;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> c_line;
      for (auto c : line) {
        if (isspace(c)) { continue; }
        c_line.push_back(c);
      }
      map.push_back(c_line);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  auto altered_map = map;

  std::pair<int, int> location;
  std::pair<int, int> direction;
  for (int row = 0; row < map.size(); ++row) {
    auto v = map[row];
    for (int col = 0; col < v.size(); ++col) {
      char c = v[col];
      if (c != '#' && c != '.') {
        location = {row, col};
        direction = p2_::initial_direction(c);
      }
      /* std::cout << c; */
    }
    /* std::cout << std::endl; */
  }
  auto initial_location = location;
  auto initial_direction = direction;

  /* std::cout << "Location: " << location.first << "," << location.second << std::endl; */
  /* std::cout << "Direction: " << direction.first << "," << direction.second << std::endl; */
  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> history;
  int num = 0;
  /* p2_::walk(map, location, direction, history, num); */
  p2_::walk(map, location, direction, history);
  int total = 1;
  for (auto v : map) {
    for (auto c : v) {
      if (c == 'X') {
        total += 1;
      }
      /* std::cout << c; */
    }
    /* std::cout << std::endl; */
  }

  auto base_map = altered_map;
  for (int row = 0; row < map.size(); ++row) {
    auto v = map[row];
    for (int col = 0; col < v.size(); ++col) {
      char c = v[col];
      if (c == 'X' && row != initial_location.first && col != initial_location.second) {
        altered_map[row][col] = '#';
        if (p2_::cycle_walk(altered_map, location, direction, history, {initial_location, initial_direction})) {
          num++;
          /* std::cout << num << std::endl; */
        }
        altered_map = base_map;
      }
    }
  }

  std::cout << num << std::endl;
  /* std::cout << total << std::endl; */

  return 0;
}

int p1() {
  std::string filename = "inputs/day6_1.txt";
  /* std::string filename = "inputs/day6_1.prod"; */
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<char>> map;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> c_line;
      for (auto c : line) {
        if (isspace(c)) { continue; }
        c_line.push_back(c);
      }
      map.push_back(c_line);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::pair<int, int> location;
  std::pair<int, int> direction;
  for (int row = 0; row < map.size(); ++row) {
    auto v = map[row];
    for (int col = 0; col < v.size(); ++col) {
      char c = v[col];
      if (c != '#' && c != '.') {
        location = {row, col};
        direction = p1_::initial_direction(c);
      }
      /* std::cout << c; */
    }
    /* std::cout << std::endl; */
  }

  /* std::cout << "Location: " << location.first << "," << location.second << std::endl; */
  /* std::cout << "Direction: " << direction.first << "," << direction.second << std::endl; */
  p1_::walk(map, location, direction);
  int total = 1;
  for (auto v : map) {
    for (auto c : v) {
      if (c == 'X') {
        total += 1;
      }
      std::cout << c;
    }
    std::cout << std::endl;
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
