#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day9_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day9_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<int64_t> ln;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      for (char c : line) {
        if (isdigit(c)) {
          ln.push_back(c - '0');
        }
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<int64_t> blocks;
  std::vector<int64_t> order;
  int64_t insert = 0;
  bool inserted = false;
  int64_t negs = 0;
  for (int64_t i = 0; i < ln.size(); ++i) {
    for (int64_t j = 0; j < ln[i]; j++) {
      if (i % 2 == 1) {
        blocks.push_back(-1);
        negs++;
      }
      else {
        blocks.push_back(insert);
        inserted = true;
        if (std::find(order.begin(), order.end(), insert) == order.end()) { order.push_back(insert); }
      }
    }
    if (inserted) { insert++; inserted = false; }
  }
  std::reverse(order.begin(), order.end());

  std::unordered_map<int64_t, std::vector<int64_t>> disk_map;
  std::unordered_map<int64_t, int64_t> map_sizes;
  p2_::get_diskMap(disk_map, map_sizes, blocks);

  std::unordered_map<int64_t, std::vector<int64_t>> negs_map;
  std::unordered_map<int64_t, int64_t> negs_sizes;
  p2_::get_negsMap(negs_map, negs_sizes, blocks);

  int64_t total = p2_::move_and_calc(blocks, order, negs_map, negs_sizes, disk_map, map_sizes);
  std::cout << total << std::endl;

  return 0;

}

int p1() {
  /* std::string filename = "inputs/day9_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day9_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<int64_t> ln;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      for (char c : line) {
        if (isdigit(c)) {
          ln.push_back(c - '0');
        }
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<int64_t> blocks;
  int64_t insert = 0;
  bool inserted = false;
  int64_t negs = 0;
  for (int64_t i = 0; i < ln.size(); ++i) {
    for (int64_t j = 0; j < ln[i]; j++) {
      if (i % 2 == 1) {
        blocks.push_back(-1);
        negs++;
      }
      else {
        blocks.push_back(insert);
        inserted = true;
      }
    }
    if (inserted) { insert++; inserted = false; }
  }

  int64_t total = p1_::move_and_calc(blocks);
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
