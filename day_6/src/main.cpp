#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

int p2() {
  return 0;
}

int p1() {
  /* std::string filename = "inputs/day5_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day5_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

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
