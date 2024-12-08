#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day8_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day8_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
  std::vector<std::vector<char>> map;

  int row = 0;
  int col = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      col = 0;
      std::vector<char> ln;
      for (auto c : line) {
        ln.push_back(c);
        if (c != '.') {
          antennas[c].push_back({row, col});
        }
        col++;
        /* std::cout << c; */
      }
      row++;
      /* std::cout << std::endl; */
      map.push_back(ln);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<std::pair<int, int>> locations;
  for (auto a : antennas) {
    /* std::cout << a.first << ": "; */
    /* for (auto l : a.second) { */
    /*   std::cout << "(" << l.first << ", " << l.second << "), "; */
    /* } */
    /* std::cout << std::endl; */
    p2_::get_antennas(a.second, {row, col}, locations);
  }

  int t = 0;
  for (auto i = 0; i < map.size(); ++i) {
    for (auto j = 0; j < map[i].size(); ++j) {
      if (std::find(locations.begin(), locations.end(), std::make_pair(i, j)) != locations.end()) {
        /* std::cout << "#"; */
        t++;
      }
      else {
        if (map[i][j] != '.' && antennas[map[i][j]].size() > 1) {
          /* std::cout << "#"; */
          t++;
        }
        else {
          /* std::cout << map[i][j]; */
        }
      }
    }
    /* std::cout << std::endl; */
  }

  std::cout << t << std::endl;

  return 0;

}

int p1() {
  /* std::string filename = "inputs/day8_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day8_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
  std::vector<std::vector<char>> map;

  int row = 0;
  int col = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      col = 0;
      std::vector<char> ln;
      for (auto c : line) {
        ln.push_back(c);
        if (c != '.') {
          antennas[c].push_back({row, col});
        }
        col++;
        std::cout << c;
      }
      row++;
      std::cout << std::endl;
      map.push_back(ln);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<std::pair<int, int>> locations;
  for (auto a : antennas) {
    std::cout << a.first << " ";
  }
  std::cout << std::endl;
  for (auto a : antennas) {
    std::cout << a.first << ": ";
    /* for (auto l : a.second) { */
    /*   std::cout << "(" << l.first << ", " << l.second << "), "; */
    /* } */
    /* std::cout << std::endl; */
    p1_::get_antennas(a.second, {row, col}, locations);
  }
  int t = 0;
  for (auto i = 0; i < map.size(); ++i) {
    for (auto j = 0; j < map[i].size(); ++j) {
      if (std::find(locations.begin(), locations.end(), std::make_pair(i, j)) != locations.end()) {
        std::cout << "#";
        t++;
      }
      else {
        std::cout << map[i][j];
      }
    }
    std::cout << std::endl;
  }
  std::cout << t << std::endl;
  /* for (auto v : map) { */
  /*   for (auto c : v) { */
  /*     std::cout << c; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */

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
