#include <cctype>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day7_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day7_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::pair<int64_t, std::vector<int64_t>>> equations;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      bool test_value = true;
      std::string str_value;
      int64_t i_value = 0;
      std::vector<int64_t> values;
      for (auto c : line) {
        if (c == ':') {
          i_value = std::stoull(str_value);
          str_value.clear();
          test_value = false;
          continue;
        }
        if (!test_value) {
          if (isspace(c) && !str_value.empty()) {
            values.push_back(std::stoi(str_value));
            str_value.clear();
            continue;
          }
        }
        str_value += c;
      }
      values.push_back(std::stoi(str_value));
      equations.push_back(std::make_pair(i_value, values));
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  int64_t total = 0;
  for (auto e : equations) {
    /* std::cout << e.first << ": "; */
    for (auto v : e.second) {
      /* std::cout << v << " "; */
    }
    /* std::cout << std::endl; */
    /* bool ret = p1_::check_ops(e.first, e.second); */
    bool ret = p2_::can_make(e.first, e.second);
    /* std::cout << e.first << std::endl; */
    if (ret) { 
      /* std::cout << "true" << std::endl;  */
      total += e.first; }
    /* else { std::cout << "false" << std::endl; } */
  }
  std::cout << "total: " << total << std::endl;

  return 0;
}

int p1() {
  /* std::string filename = "inputs/day7_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day7_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::pair<int64_t, std::vector<int64_t>>> equations;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      bool test_value = true;
      std::string str_value;
      int64_t i_value = 0;
      std::vector<int64_t> values;
      for (auto c : line) {
        if (c == ':') {
          i_value = std::stoull(str_value);
          str_value.clear();
          test_value = false;
          continue;
        }
        if (!test_value) {
          if (isspace(c) && !str_value.empty()) {
            values.push_back(std::stoi(str_value));
            str_value.clear();
            continue;
          }
        }
        str_value += c;
      }
      values.push_back(std::stoi(str_value));
      equations.push_back(std::make_pair(i_value, values));
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  int64_t total = 0;
  for (auto e : equations) {
    /* std::cout << e.first << ": "; */
    for (auto v : e.second) {
      /* std::cout << v << " "; */
    }
    /* std::cout << std::endl; */
    /* bool ret = p1_::check_ops(e.first, e.second); */
    bool ret = p1_::can_make(e.first, e.second);
    /* std::cout << e.first << std::endl; */
    if (ret) { 
      /* std::cout << "true" << std::endl;  */
      total += e.first; }
    /* else { std::cout << "false" << std::endl; } */
  }
  std::cout << "total: " << total << std::endl;

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
