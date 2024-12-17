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

  bool isvalid(std::pair<int64_t, int64_t> c_l, std::pair<int64_t, int64_t> m_b) {
    return 
      c_l.first < m_b.first &&
      c_l.first > 0 &&
      c_l.second < m_b.second &&
      c_l.second > 0;
  }

  bool check_push(
      std::pair<int64_t, int64_t> location,
      std::pair<int64_t, int64_t> direction,
      std::pair<int64_t, int64_t> map_bounds,
      std::vector<std::vector<int64_t>> map,
      std::vector<std::tuple<int64_t, int64_t, int64_t>> &changed,
      int64_t previous) {

    std::pair<int64_t, int64_t> ch_l = {
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
      std::cout << previous << std::endl;
      int64_t t_p = 1;
      if (check_push(ch_l, direction, map_bounds, map, changed, t_p)) {
        changed.push_back(std::make_tuple(ch_l.first, ch_l.second, previous));
        return true;
      }
    }

    return false;
  }

}
