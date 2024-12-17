#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "coordinate.h"

namespace p2_ {

  bool isvalid(std::pair<coordinate, coordinate> c_l, std::pair<int64_t, int64_t> m_b) {
    bool lead = 
      c_l.first.x < m_b.first && 
      c_l.first.x > 0 && 
      c_l.first.y < m_b.second && 
      c_l.first.y > 0;

    bool follow = 
      c_l.first.x < m_b.first && 
      c_l.first.x > 0 && 
      c_l.first.y < m_b.second && 
      c_l.first.y > 0;

    return lead && follow;
  }

  bool check_box(
      box location,
      coordinate im_l,
      std::pair<int64_t, int64_t> direction,
      std::pair<int64_t, int64_t> map_bounds,
      std::vector<std::vector<int64_t>> imap,
      std::vector<std::vector<std::pair<box, int64_t>>> map,
      std::vector<std::tuple<coordinate, int64_t>> &changed,
      int64_t previous_f, int64_t previous_s) {
    return false;
  }

  bool check_push(
      box location,
      coordinate im_l,
      std::pair<int64_t, int64_t> direction,
      std::pair<int64_t, int64_t> pdirection,
      std::pair<int64_t, int64_t> map_bounds,
      std::vector<std::vector<int64_t>> imap,
      std::vector<std::vector<std::pair<box, int64_t>>> map,
      std::vector<std::tuple<box, coordinate, int64_t>> &changed) {

    coordinate c_iml = { im_l.x + direction.first, im_l.y + direction.second };

    coordinate ch_ll;
    ch_ll.x = location.first.x + direction.first;
    ch_ll.y = location.first.y + direction.second;
    coordinate ch_lf;
    ch_lf.x = location.second.x + pdirection.first;
    ch_lf.y = location.second.y + pdirection.second;
    std::pair<coordinate, coordinate> ch_l = std::make_pair(ch_ll, ch_lf);

    if (!isvalid(ch_l, map_bounds)) { return false; }

    if (map[c_iml.x][c_iml.y].second == -1) { return false; }
    else if (map[c_iml.x][c_iml.y].second == 0) { 
      changed.push_back(std::make_tuple(map[c_iml.x][c_iml.y].first, c_iml, 0)); 
      return true; 
    }
    else if (map[c_iml.x][c_iml.y].second == 2) { 
      // just swap coordinates (follow with lead)
      changed.push_back(std::make_tuple(map[c_iml.x][c_iml.y].first, c_iml, 2)); 
      return true; 
    }
    else if (map[ch_ll.x][ch_ll.y].second == 1) {
      /* if (check_push(ch_l, direction, pdirection, map_bounds, map, changed, t_p)) { */
      /*   changed.push_back(std::make_tuple(ch_l.first, ch_l.second, previous_l, previous_f)); */
      /*   return true; */
      /* } */
    }

    return false;
  }

}
