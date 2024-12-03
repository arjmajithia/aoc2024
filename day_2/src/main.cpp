#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

bool check_if_valid(std::vector<int> input) {
  bool descending = false;

  if (input[0] < input[1]) { descending = false; }
  else { descending = true; }

  for (int i = 1; i < input.size(); ++i) {
    if (descending && input[i] > input[i-1]) { return false; } 
    else if (!descending && input[i] < input[i-1]) { return false; } 
    else if (input[i] == input[i-1]) { return false; }
    if (std::abs(input[i] - input[i-1]) > 3) { return false; }
  }
  return true;
}

int p2() {
  /* std::string filename = "inputs/day1_2.txt"; */
  std::string filename = "inputs/day1_2.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::unordered_map<int, std::vector<int>> report_map;

  int line_num = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<int> report;
      std::string str_value;
      for (int i = 0; i < line.length(); ++i) {
        if (isspace(line[i])) { 
          report.push_back(std::atoi(str_value.c_str()));
          str_value.clear();
          continue; 
        }
        str_value += line[i];
      }
      report.push_back(std::atoi(str_value.c_str()));
      str_value.clear();

      report_map[line_num] = std::move(report);
      line_num++;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  bool broken = false;
  std::vector<int> invalids;
  std::vector<int> valids;
  /* std::cout << report_map.size() << std::endl; */
  for (int j = 0; j < report_map.size(); ++j) {
    auto r = report_map[j];
    bool descending = false;

    if (r[0] < r[1]) { descending = false; }
    else { descending = true; }

    for (int i = 1; i < r.size(); ++i) {
      if (!check_if_valid(r)) {
        invalids.push_back(j); broken = true;
        break;
      }
    }
    if (!broken) {
      valids.push_back(j);
    }
    broken = false;
  }

  for (auto j : invalids) {
    auto v = report_map[j];
    for (int i = 0; i < v.size(); ++i) {
      auto copy_v = v;
      copy_v.erase(copy_v.begin() + i);
      if (check_if_valid(copy_v)) {
        valids.push_back(j);
        break;
      }
    }
  }

  std::cout << "Valids size: " << valids.size() << std::endl;

  return 0;
}

int p1() {
  /* std::string filename = "inputs/day1_1.txt"; */
  std::string filename = "inputs/day1_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::unordered_map<int, std::vector<int>> report_map;

  int line_num = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<int> report;
      std::string str_value;
      for (int i = 0; i < line.length(); ++i) {
        if (isspace(line[i])) { 
          report.push_back(std::atoi(str_value.c_str()));
          str_value.clear();
          continue; 
        }
        str_value += line[i];
      }
      report.push_back(std::atoi(str_value.c_str()));
      str_value.clear();

      report_map[line_num] = std::move(report);
      line_num++;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  bool broken = false;
  std::vector<int> invalids;
  std::vector<int> valids;
  /* std::cout << report_map.size() << std::endl; */
  for (int j = 0; j < report_map.size(); ++j) {
    auto r = report_map[j];
    bool descending = false;

    if (r[0] < r[1]) { descending = false; }
    else { descending = true; }

    for (int i = 1; i < r.size(); ++i) {
      if (!check_if_valid(r)) {
        invalids.push_back(j); broken = true;
        break;
      }
      /* if (descending && r[i] > r[i-1]) { */
      /*   invalids.push_back(j); broken = true; */
      /*   break; */
      /* } else if (!descending && r[i] < r[i-1]) { */
      /*   invalids.push_back(j); broken = true; */
      /*   break; */
      /* } else if (r[i] == r[i-1]) { */
      /*   invalids.push_back(j); broken = true; */
      /*   break; */
      /* } */
      /* if (std::abs(r[i] - r[i-1]) > 3) { */
      /*   invalids.push_back(j); broken = true; */
      /*   break; */
      /* } */
    }
    if (!broken) {
      valids.push_back(j);
    }
    broken = false;
    /* std::cout << std::endl; */
    /* auto ret = std::is_sorted(r.second.begin(), r.second.end(),  */
    /*     [](const int &a, const int &b){ return (std::abs(a-b) < 2); }); */
    /* std::cout << ret << std::endl; */
  }
  std::cout << "Valid count: " << valids.size() << std::endl;

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
