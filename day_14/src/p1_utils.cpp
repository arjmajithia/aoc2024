#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>

#include "main.h"

namespace p1_ {

  int64_t solve_p1(
      std::vector<Robot> robots,
      std::pair<int64_t, int64_t> limits,
      std::pair<int64_t, int64_t> qlimits,
      std::unordered_map<int64_t, int64_t> quadrants) {

    for (auto r : robots) {
      r.move_X(limits, 100);
      int64_t qd = r.get_quadrant(qlimits);
      quadrants[qd]++;
    }

    int64_t total = 1;
    for (auto q : quadrants) {
      if (q.first == 0) { continue; }
      total *= q.second;
      /* std::cout << "Quad " << q.first << " has " << q.second << " guards" << std::endl; */
    }

    return total;
  }
}
