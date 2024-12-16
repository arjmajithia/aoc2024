#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/integer/mod_inverse.hpp>

#include "main.h"

namespace p2_ {

  int64_t posMod(int64_t a, int64_t m) { return ((a % m) + m) % m; }

  int64_t get_variance(std::vector<int64_t> ve) {
    int64_t sum = std::accumulate(ve.begin(), ve.end(), 0);
    int64_t m = sum / ve.size();

    int64_t accum = 0;
    std::for_each(ve.begin(), ve.end(), [&](const int64_t d){ accum += (d - m) * (d - m); });

    int64_t variance = (accum) / (ve.size() - 1);
    return variance;
  }

  void printmap(
      std::vector<Robot> robots,
      std::pair<int64_t, int64_t> limits,
      int64_t step) {

    std::vector<std::pair<int64_t, int64_t>> r_ls;
    for (auto r : robots) {
      std::pair<int64_t, int64_t> step_location = r.steps(limits, step);
      r_ls.push_back(step_location);
    }
    std::cout << limits.first << ", " << limits.second << std::endl;

    for (int64_t i = 0; i < limits.second; ++i) {
      for (int64_t j = 0; j < limits.first; ++j) {
        if (std::find(r_ls.begin(), r_ls.end(), std::make_pair(j, i)) != r_ls.end()) {
          std::cout << "#";
        }
        else {
          std::cout << ".";
        }
      }
      std::cout << std::endl;
    }
  }

  int64_t solve_p2(
      std::vector<Robot> robots,
      std::pair<int64_t, int64_t> limits,
      std::pair<int64_t, int64_t> qlimits,
      std::unordered_map<int64_t, int64_t> quadrants) {

    int64_t lx, ly = 0;
    int64_t lxvar, lyvar = 10*1000;
    int64_t max_l = std::max(limits.first, limits.second);
    int64_t invColmodRow = boost::integer::mod_inverse(limits.first, limits.second);

    for (int64_t i = 0; i < max_l; ++i) {
      std::vector<int64_t> xs;
      std::vector<int64_t> ys;
      for (auto r : robots) {
        std::pair<int64_t, int64_t> step_location = r.steps(limits, i);
        xs.push_back(step_location.first); ys.push_back(step_location.second);
      }
      int64_t xvar = get_variance(xs);
      int64_t yvar = get_variance(ys);

      if (xvar < lxvar) { lx = i; lxvar = xvar; }
      if (yvar < lyvar) { ly = i; lyvar = yvar; }
    }

    auto tmp = posMod((invColmodRow * (ly - lx)), limits.second);
    int64_t total = lx + (posMod((invColmodRow * (ly - lx)), limits.second)) * limits.first;
    printmap(robots, limits, total);
    return total;
  }

}
