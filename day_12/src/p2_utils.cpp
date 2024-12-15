#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace p2_ {

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

  struct checkRegion {
    int minX;
    int minY;
    int maxX;
    int maxY;
  };

  void get_region(
      std::vector<std::string> &map,
      std::vector<std::vector<bool>> &visited_map,
      std::vector<std::vector<bool>> &visited_group,
      char type,
      int &area,
      checkStruct checker,
      checkRegion &region,
      std::pair<int, int> location) {

    if (!checker.check(location) || 
        map.at(location.first).at(location.second) != type) {
      region.minX = std::min(region.minX, location.first);
      region.maxX = std::max(region.maxX, location.first);
      region.minY = std::min(region.minY, location.second);
      region.maxY = std::max(region.maxY, location.second);
      return;
    }

    if (visited_group.at(location.first).at(location.second)) { return; }
    
    visited_map.at(location.first).at(location.second) = true;
    visited_group.at(location.first).at(location.second) = true;
    
    area++;

    get_region(map, visited_map, visited_group, type, area, checker, region, std::make_pair(location.first + 1, location.second));
    get_region(map, visited_map, visited_group, type, area, checker, region, std::make_pair(location.first - 1, location.second));
    get_region(map, visited_map, visited_group, type, area, checker, region, std::make_pair(location.first, location.second + 1));
    get_region(map, visited_map, visited_group, type, area, checker, region, std::make_pair(location.first, location.second - 1));
  }

  int get_price(std::vector<std::string> &map) {
    checkStruct checker;
    checker.maxX = map.size() - 1;
    checker.minX = 0;
    checker.maxY = map.front().length() - 1;
    checker.minY = 0;

    std::vector<std::vector<bool>> visited_map(
        checker.maxX + 1,
        std::vector<bool>(checker.maxY + 1, false));

    int total = 0;
    for (int i = 0; i < checker.maxX + 1; ++i) {
      for (int j = 0; j < checker.maxY + 1; ++j) {
        if (visited_map.at(i).at(j)) { continue; }
        int area = 0; 
        std::vector<std::vector<bool>> visited_group(
            checker.maxX + 1,
            std::vector<bool>(checker.maxY + 1, false));
        checkRegion region;
        region.minX = std::numeric_limits<int>::max();
        region.minY = std::numeric_limits<int>::max();
    
        /* std::cout << map.at(i).at(j) << std::endl; */
        get_region(map, visited_map, visited_group, map.at(i).at(j), area, checker, region, {i, j});
        /* std::cout << region.minX << ", " << region.maxX << std::endl; */
        /* std::cout << region.minY << ", " << region.maxY << std::endl; */
    
        int sides = 0;
        for (int a = region.minX; a < region.maxX; ++a) {
          for (int b = region.minY; b < region.maxY; ++b) {
            bool topleft, topright, botleft, botright = false;
            if (checker.check({a, b})) {
              topleft = visited_group.at(a).at(b) && map.at(a).at(b) == map.at(i).at(j);
            }
            if (checker.check({a, b + 1})) {
              topright = visited_group.at(a).at(b + 1) && map.at(a).at(b + 1) == map.at(i).at(j);
            }
            if (checker.check({a + 1, b})) {
              botleft = visited_group.at(a + 1).at(b) && map.at(a + 1).at(b) == map.at(i).at(j);
            }
            if (checker.check({a + 1, b + 1})) {
              botright = visited_group.at(a + 1).at(b + 1) && map.at(a + 1).at(b + 1) == map.at(i).at(j);
            }
    
            int per = topleft + topright + botleft + botright;
            if (map.at(i).at(j) == 'D') {
              std::cout << map.at(i).at(j) << std::endl;
              std::cout << a << ", " << b << std::endl;
              std::cout << "Perimeter: " << per << std::endl;

              sides += (per % 2 == 1);
              if (per == 2) { 
                /* std::cout << topleft << " " << botright << " | " << (topleft && botright) << std::endl; */
                /* std::cout << botleft << " " << topright << " | " << (botleft && topright) << std::endl; */
                sides += 2 * ((topleft && botright) || (botleft && topright)); 

              }
            }
            /* std::cout << sides << std::endl; */
          }
        }
        std::cout << "Sides: " << sides << " area: " << area << std::endl;
        total += area * sides;
      }
    }
    return total;
  }

}
