#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "main.h"

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int main() {
  /* std::string filename = "inputs/day14_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day14_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<Robot> robots;

  /* std::pair<int64_t, int64_t> t_limits = {11, 7}; */
  std::pair<int64_t, int64_t> t_limits = {11, 7};
  std::pair<int64_t, int64_t> limits = {101, 103};

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      Robot robot;
      std::string loc_vals = line.substr(0, line.find(' '));
      loc_vals = loc_vals.substr(loc_vals.find("=")+1);
      std::string dir_vals = line.substr(line.find(' '));
      dir_vals = dir_vals.substr(dir_vals.find("=")+1);

      auto xp = loc_vals.substr(0, loc_vals.find(","));
      auto yp = loc_vals.substr(loc_vals.find(",")+1);
      auto xd = dir_vals.substr(0, dir_vals.find(","));
      auto yd = dir_vals.substr(dir_vals.find(",")+1);

      robot.location = std::make_pair(std::stoll(xp), std::stoll(yp));
      robot.direction = std::make_pair(std::stoll(xd), std::stoll(yd));
      robots.push_back(robot);
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::pair<int64_t, int64_t> tquad_limits = {(t_limits.first - 1) / 2, (t_limits.second - 1) / 2};
  std::pair<int64_t, int64_t> quad_limits = {(limits.first - 1) / 2, (limits.second - 1) / 2};
  std::unordered_map<int64_t, int64_t> quadrants;
  int64_t total = 0;

#ifdef PART1
  total += p1_::solve_p1(robots, limits, quad_limits, quadrants);
#endif
#ifndef PART1
  total += p2_::solve_p2(robots, limits, quad_limits, quadrants);
#endif

  std::cout << total << std::endl;
  return 0;
}
