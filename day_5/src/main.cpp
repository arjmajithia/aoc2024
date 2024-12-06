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

std::unordered_map<int, std::unordered_set<int>> rules;

bool customSort(int lhs, int rhs) {
  if (rules[lhs].find(rhs) != rules[lhs].end()) {
    return true;
  }
  return false;
}

int p2() {
  /* std::string filename = "inputs/day5_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day5_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::vector<int>> orders;
  rules.clear();

  bool read_orders = false;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      if (line.find_first_not_of(' ') == std::string::npos) {
        read_orders = true;
        continue;
      }
      if (read_orders) { 
        std::vector<int> nums;
        std::string str_value;
        for (auto c : line) {
          if (c == ',') {
            nums.push_back(std::stoi(str_value));
            str_value.clear();
          }
          else { str_value += c; }
        }
        orders.push_back(nums);
      }
      else {
        int key;
        int value;
        std::string str_value;
        for (auto c : line) {
          if (c == '|') {
            key = std::stoi(str_value);
            str_value.clear();
            continue;
          }
          if (c != ' ' || c != ',') {
            str_value += c;
          }
        }
        value = std::stoi(str_value);
        rules[key].insert(value);
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  int sum = 0;
  for (auto o : orders) {
    auto presort = o;
    std::sort(o.begin(), o.end(), customSort);
    if (presort != o) {
      sum += o[o.size()/2];
    }
  }
  std::cout << sum << std::endl;

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
  std::vector<std::vector<int>> orders;
  rules.clear();

  bool read_orders = false;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      if (line.find_first_not_of(' ') == std::string::npos) {
        read_orders = true;
        continue;
      }
      if (read_orders) { 
        std::vector<int> nums;
        std::string str_value;
        for (auto c : line) {
          if (c == ',') {
            nums.push_back(std::stoi(str_value));
            str_value.clear();
          }
          else { str_value += c; }
        }
        orders.push_back(nums);
      }

      else {
        int key;
        int value;
        std::string str_value;
        for (auto c : line) {
          if (c == '|') {
            key = std::stoi(str_value);
            str_value.clear();
            continue;
          }
          if (c != ' ' || c != ',') {
            str_value += c;
          }
        }
        value = std::stoi(str_value);
        rules[key].insert(value);
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  int sum = 0;
  for (auto o : orders) {
    auto presort = o;
    std::sort(o.begin(), o.end(), customSort);
    if (presort == o) {
      sum += o[o.size()/2];
    }
  }
  std::cout << sum << std::endl;

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
