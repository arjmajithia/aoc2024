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
  return 0;
}

int p1() {
  std::string filename = "inputs/day17_1.txt";
  /* std::string filename = "inputs/tmp"; */
  /* std::string filename = "inputs/day17_1.prod"; */
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<int64_t> reg_a, reg_b, reg_c, program;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      if (line.find_first_not_of(' ') == std::string::npos) { continue; }
      std::string pre_c = line.substr(0, line.find(":"));
      std::string post_c = line.substr(line.find(":") + 2);
      std::string str_val;

      if (pre_c.find("A") != std::string::npos) { 
        for (auto c : post_c) {
          if (isspace(c)) { continue; }
          if (!isdigit(c)) { 
            reg_b.push_back(std::stoll(str_val)); 
            str_val.clear();
            continue;
          }
          str_val += c;
        }
        if (!str_val.empty()) { reg_a.push_back(std::stoll(str_val)); str_val.clear(); }
      }
      else if (pre_c.find("B") != std::string::npos) { 
        for (auto c : post_c) {
          if (isspace(c)) { continue; }
          if (isspace(c) || !isdigit(c)) { 
            reg_b.push_back(std::stoll(str_val)); 
            str_val.clear();
            continue;
          }
          str_val += c;
        }
        if (!str_val.empty()) { reg_b.push_back(std::stoll(str_val)); str_val.clear(); }
      }
      else if (pre_c.find("C") != std::string::npos) { 
        for (auto c : post_c) {
          if (isspace(c) || !isdigit(c)) { 
            reg_c.push_back(std::stoll(str_val)); 
            str_val.clear();
            continue;
          }
          str_val += c;
        }
        if (!str_val.empty()) { reg_c.push_back(std::stoll(str_val)); str_val.clear(); }
      }
      else if (pre_c.find("Program") != std::string::npos) { 
        for (auto c : post_c) {
          if (c == ',') { 
            program.push_back(std::stoll(str_val)); 
            str_val.clear();
            continue;
          }
          str_val += c;
        }
        if (!str_val.empty()) { program.push_back(std::stoll(str_val)); str_val.clear(); }
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  /* std::cout << "Reg A" << std::endl; */
  /* for (auto v : reg_a) { */
  /*   std::cout << v << std::endl; */
  /* } */
  /* std::cout << "Reg B" << std::endl; */
  /* for (auto v : reg_b) { */
  /*   std::cout << v << std::endl; */
  /* } */
  /* std::cout << "Reg C" << std::endl; */
  /* for (auto v : reg_c) { */
  /*   std::cout << v << std::endl; */
  /* } */
  /* std::cout << "Program" << std::endl; */
  /* for (auto v : program) { */
  /*   std::cout << v << std::endl; */
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
