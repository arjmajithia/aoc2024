#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

int p2() {
  std::vector<int> col1, col2;
  /* std::string filename = "inputs/day1_1.txt"; */
  std::string filename = "inputs/day1_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  bool filled_1 = false;
  bool filled_2 = false;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::string str_value;
      for (int i = 0; i < line.length(); ++i) {
        if (i > 0) { 
          if (line[i] == line[i-1] && isspace(line[i])) { continue; } 
        }
        char c = line[i];
        if (isspace(c) || i == line.length() - 1) { 
          if (i == line.length() - 1) { str_value += c; }
          if (!filled_1) {
            col1.push_back(std::atoi(str_value.c_str()));
            filled_1 = true;
            str_value.clear();
          }
          else if (!filled_2) {
            col2.push_back(std::atoi(str_value.c_str()));
            filled_2 = true;
            str_value.clear();
          }
          str_value.clear();
        }
        str_value += c;
      }
      filled_1 = false;
      filled_2 = false;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  if (col1.size() != col2.size()) {
    std::cout << "Column 1 is not the same size as Column 2. Breaking." << std::endl;
    return 1;
  }

  std::sort(col1.begin(), col1.end());
  std::sort(col2.begin(), col2.end());

  int total = 0;
  std::unordered_map<int, int> c2_freq;
  for (auto v : col2) {
    ++c2_freq[v];
  }
  for (int i : col1) {
    /* std::cout << "val " << i << " in c1 appears " << c2_freq[i] << " in c2\n"; */
    total += i * c2_freq[i];
  }
  std::cout << total << std::endl;

  return 0;
}

int p1() {
  std::vector<int> col1, col2;
  /* std::string filename = "inputs/day1_1.txt"; */
  std::string filename = "inputs/day1_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  bool filled_1 = false;
  bool filled_2 = false;

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::string str_value;
      for (int i = 0; i < line.length(); ++i) {
        if (i > 0) { 
          if (line[i] == line[i-1] && isspace(line[i])) { continue; } 
        }
        char c = line[i];
        if (isspace(c) || i == line.length() - 1) { 
          if (i == line.length() - 1) { str_value += c; }
          if (!filled_1) {
            col1.push_back(std::atoi(str_value.c_str()));
            filled_1 = true;
            str_value.clear();
          }
          else if (!filled_2) {
            col2.push_back(std::atoi(str_value.c_str()));
            filled_2 = true;
            str_value.clear();
          }
          str_value.clear();
        }
        str_value += c;
      }
      filled_1 = false;
      filled_2 = false;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::sort(col1.begin(), col1.end());
  std::sort(col2.begin(), col2.end());

  if (col1.size() != col2.size()) {
    std::cout << "Column 1 is not the same size as Column 2. Breaking." << std::endl;
    return 1;
  }

  int total = 0;
  for (int i = 0; i < col1.size(); ++i) {
    int difference = std::abs((col1[i] - col2[i]));
    total += difference;
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
