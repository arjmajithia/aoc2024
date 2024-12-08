#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <iostream>

namespace p2_ {

  std::unordered_map<std::string, std::pair<int,int>> path_swap( {
      { "1, 0", {0, -1} },
      { "-1, 0", {0, 1} },
      { "0, 1", {1, 0} },
      { "0, -1", {-1, 0} }
      });

  std::pair<int, int> initial_direction(char c) {
    if (c == '>') { return {0,1}; }
    else if (c == '<') { return {0,-1}; }
    else if (c == '^') { return {-1,0}; }
    else if (c == 'v') { return {1,0}; }
    else { return {0,0}; }
  }

  bool check_valid_direction(
      std::pair<int, int> check_location, 
      std::pair<int, int> dimensions) {

    if (check_location.first >= dimensions.first) {
      return false;
    } else if (check_location.first < 0) {
      return false;
    }
    if (check_location.second >= dimensions.second) {
      return false;
    } else if (check_location.second < 0) {
      return false;
    }
    return true;
  }

  std::pair<int, int> _90deg_turn(std::pair<int, int> direction) {
    std::string map_key = std::to_string(direction.first) + 
      ", " + std::to_string(direction.second);
    std::pair<int, int> rdirection = path_swap[map_key];
    return rdirection;
  }

  void walk(
      std::vector<std::vector<char>> &map,
      std::pair<int, int> location,
      std::pair<int, int> direction,
      std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> history) {

    std::pair<int, int> check_loc = 
      { location.first + direction.first, location.second + direction.second };

    if (check_valid_direction(check_loc, { map.size(), map[0].size() } )) {
      if (map[check_loc.first][check_loc.second] == '#') {
        direction = _90deg_turn(direction);
        check_loc = location;
      } else {
        map[check_loc.first][check_loc.second] = 'X';
        history.push_back({check_loc, direction});
        /* auto rdirection = _90deg_turn(direction); */
        /* std::pair<int, int> test_loc =  */
        /*   { check_loc.first + rdirection.first, check_loc.second + rdirection.second }; */
        /* while (check_valid_direction(test_loc, {map.size(), map[0].size()})) { */
        /*   if (std::find(history.begin(), history.end(), std::make_pair(test_loc, rdirection))  */
        /*       != history.end()) { */
        /*     num++; */
        /*     break; */
        /*   } */
        /*   test_loc = { test_loc.first + rdirection.first, test_loc.second + rdirection.second }; */
        /* } */
      }
      /* walk(map, check_loc, direction, history, num); */
      walk(map, check_loc, direction, history);
    } 
  }

  bool cycle_walk(
      std::vector<std::vector<char>> &map,
      std::pair<int, int> location,
      std::pair<int, int> direction,
      std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> history,
      std::pair<std::pair<int, int>, std::pair<int, int>> initial_) {

    std::pair<int, int> check_loc = 
      { location.first + direction.first, location.second + direction.second };

    if (check_valid_direction(check_loc, { map.size(), map[0].size() } )) {
      if (std::find(history.begin(), history.end(), std::make_pair(check_loc, direction)) 
          != history.end()) {
        return true;
      }
      if (map[check_loc.first][check_loc.second] == '#') {
        direction = _90deg_turn(direction);
        check_loc = location;
      } else {
        map[check_loc.first][check_loc.second] = 'X';
        history.push_back({check_loc, direction});
      }
      return cycle_walk(map, check_loc, direction, history, initial_);
    } 
    return false;
  }

  void cycle_detect(
      std::vector<std::vector<char>> altered_map,
      std::pair<int, int> location,
      std::pair<int, int> direction,
      std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> history,
      int &num) {
  }

}
