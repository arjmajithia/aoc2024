#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int p2() {
  /* std::string filename = "inputs/day11_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day11_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<uint64_t> ln;
  std::vector<std::string> str_ln;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::string str_val;
      for (auto c : line) {
        if (isspace(c)) {
          ln.push_back(std::stoll(str_val));
          str_ln.push_back(str_val);
          str_val.clear();
          continue;
        }
        str_val += c;
      }
      ln.push_back(std::stoi(str_val));
      str_ln.push_back(str_val);
      str_val.clear();
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  uint64_t total = 0;
  for (auto v : ln) {
    uint64_t val = p2_::solve(std::make_pair(v, 75));
    total += val;
  }
  std::cout << total << std::endl;

  return 0;
}

int p1() {
  /* std::string filename = "inputs/day11_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day11_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<int64_t> ln;
  std::vector<std::string> str_ln;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::string str_val;
      for (auto c : line) {
        if (isspace(c)) {
          ln.push_back(std::stoi(str_val));
          str_ln.push_back(str_val);
          str_val.clear();
          continue;
        }
        str_val += c;
      }
      ln.push_back(std::stoi(str_val));
      str_ln.push_back(str_val);
      str_val.clear();
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::vector<int64_t> nline;
  std::vector<std::string> sline;

  /* std::cout << "After 1" << std::endl; */
  std::tie(nline, sline) = p1_::check(ln, str_ln, nline, sline);
  /* for (auto v : nline) { */
  /*   std::cout << v << " "; */
  /* } */
  /* std::cout << std::endl; */

  for (int64_t i = 1; i < 25; ++i) {
    std::vector<int64_t> out_nline;
    std::vector<std::string> out_sline;
    /* std::cout << "After " << i+1 << std::endl; */
    std::tie(nline, sline) = p1_::check(nline, sline, out_nline, out_sline);
    /* for (auto v : nline) { */
    /*   std::cout << v << " "; */
    /* } */
    /* std::cout << std::endl; */
  }

  /* for (auto v : nline) { */
  /*   std::cout << v << " "; */
  /* } */
  /* std::cout << std::endl; */
  std::cout << nline.size() << std::endl;

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
