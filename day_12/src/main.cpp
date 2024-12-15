#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  std::string filename = "inputs/day12_1.txt";
  /* std::string filename = "inputs/tmp"; */
  /* std::string filename = "inputs/tmp2"; */
  /* std::string filename = "inputs/day12_1.prod"; */
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::string> map;

  if (input_file.is_open()) {
    int row = 0;
    while(std::getline(input_file, line))
    {
      int col = 0;
      map.push_back(line);
      row++;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  int total = p2_::get_price(map);
  std::cout << total << std::endl;

  return 0;

}

int p1() {
  /* std::string filename = "inputs/day12_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  /* std::string filename = "inputs/tmp2"; */
  std::string filename = "inputs/day12_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::string> map;

  if (input_file.is_open()) {
    int row = 0;
    while(std::getline(input_file, line))
    {
      int col = 0;
      map.push_back(line);
      row++;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  int total = p1_::get_price(map);
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
