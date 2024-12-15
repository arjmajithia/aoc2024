#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace p1_ {

  struct checkStruct {
    int minX;
    int minY;
    int maxX;
    int maxY;

    bool check(std::pair<int, int> location) {
      return location.first >= minX && location.first <= maxX 
        && location.second >= minY && location.second <= maxY;
    }
  };

  void get_region(
      std::vector<std::string> &map,
      std::vector<std::vector<bool>> &visited,
      char type,
      int &area,
      int &perimeter,
      std::pair<int, int> location,
      checkStruct checker) {

    if (!checker.check(location) || 
        map.at(location.first).at(location.second) != type) {
      perimeter++; return;
    }
    if (visited.at(location.first).at(location.second)) { return; }
    visited.at(location.first).at(location.second) = true;
    area++;

    get_region(map, visited, type, area, perimeter, 
        std::make_pair(location.first + 1, location.second), checker);
    get_region(map, visited, type, area, perimeter, 
        std::make_pair(location.first - 1, location.second), checker);
    get_region(map, visited, type, area, perimeter, 
        std::make_pair(location.first, location.second + 1), checker);
    get_region(map, visited, type, area, perimeter, 
        std::make_pair(location.first, location.second - 1), checker);
  }

  int get_price(std::vector<std::string> &map) {
    checkStruct checker;
    checker.maxX = map.size() - 1;
    checker.maxY = map.front().length() - 1;

    std::vector<std::vector<bool>> visited(
        checker.maxX + 1,
        std::vector<bool>(checker.maxY + 1, false));

    int total = 0;
    for (int i = 0; i < checker.maxX + 1; ++i) {
      for (int j = 0; j < checker.maxY + 1; ++j) {
        if (visited.at(i).at(j)) { continue; }
        int area = 0; 
        int perimeter = 0;
        get_region(map, visited, map.at(i).at(j), area, perimeter, {i , j}, checker);
        total += area * perimeter;
      }
    }
    return total;
  }



  std::array<std::pair<int, int>, 4> old_directions = {
    {{-1, 0},
      {1, 0},
      {0, -1},
      {0, 1}}
  };

  int old_get_perimeter(std::set<std::pair<int, int>> input) {
    int peri = input.size() * 4;
    for (int i = 0; i < input.size(); ++i) {
      std::pair<int, int> to_check = *std::next(input.begin(), i);
      int adj = 0;
      for (auto p : input) {
        if (to_check == p) { continue; }
        else {
          int distance = std::ceil(std::sqrt(
              std::pow(p.first - to_check.first, 2) + 
              std::pow(p.second - to_check.second, 2)));
          if (distance == 1) { adj += 1; }
        }
      }
      peri -= adj;
    }
    return peri;
  }

  std::set<std::pair<int, int>> old_check_adjacency(
      std::vector<std::pair<int, int>> list,
      int center_index) {
    std::set<std::pair<int, int>> out;
    std::pair<int, int> group_center = list[center_index];
    out.insert(group_center);

    for (auto l : list) {
      for (auto c : out) {
        int distance = std::sqrt(
            std::pow(l.first - c.first, 2) + 
            std::pow(l.second - c.second, 2));
      
        if (distance != 1) { continue; }
        out.insert(l);
      }
    }
    return out;
  }

}

/* std::unordered_map<char, std::vector<std::pair<int, int>>> plots; */
/* for (char c : line) { */
/*   plots[c].push_back({row, col}); */
/*   col++; */
/* } */
/* std::cout << line << std::endl; */
/* for (auto p : plots) { */
/*   std::vector<std::set<std::pair<int, int>>> full; */
/*   for (int i = 0; i < p.second.size(); ++i) { */
/*     std::set<std::pair<int, int>> tmp; */
/*     tmp = p1_::check_adjacency(p.second, i); */
/*  */
/*     if (full.size() == 0) { full.push_back(tmp); } */
/*     bool commons = true; */
/*     for (std::set<std::pair<int, int>> &s : full) { */
/*       std::vector<std::pair<int, int>> intersect; */
/*       std::set_intersection(s.begin(), s.end(), tmp.begin(), tmp.end(), std::back_inserter(intersect)); */
/*  */
/*       if (intersect.size() > 1) {  */
/*         s.insert(tmp.begin(), tmp.end()); */
/*         commons = false; */
/*         continue; */
/*       } */
/*     } */
/*     if (commons) { */
/*       full.push_back(tmp); */
/*     } */
/*   } */
/*   for (auto group : full) { */
/*     int area = group.size(); */
/*     int perimeter = p1_::get_perimeter(group); */
/*     total += perimeter * area; */
/*   } */
/* } */

