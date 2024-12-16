#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>

namespace p1_ {

  bool isvalid(std::pair<int, int> c_l, std::pair<int, int> m_b) {
    return 
      c_l.first < m_b.first &&
      c_l.first > 0 &&
      c_l.second < m_b.second &&
      c_l.second > 0;
  }

  bool check_push(
      std::pair<int, int> location,
      std::pair<int, int> direction,
      std::pair<int, int> map_bounds,
      std::vector<std::vector<int>> map,
      std::vector<std::tuple<int, int, int>> &changed,
      int previous) {

    std::pair<int, int> ch_l = {
      location.first + direction.first, 
      location.second + direction.second};

    if (!isvalid(ch_l, map_bounds)) { return false; }

    if (map[ch_l.first][ch_l.second] == -1) { return false; }
    else if (map[ch_l.first][ch_l.second] == 0) { 
      // x, y, type
      changed.push_back(std::make_tuple(ch_l.first, ch_l.second, previous));
      return true;
    }
    else if (map[ch_l.first][ch_l.second] == 1) { 
      if (check_push(ch_l, direction, map_bounds, map, changed, previous)) {
        std::cout << previous << "| ";
        int t_p = 1;
        changed.push_back(std::make_tuple(ch_l.first, ch_l.second, t_p));
        return true;
      }
    }

    return false;
  }

}
