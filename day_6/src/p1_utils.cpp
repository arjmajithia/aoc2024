#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <iostream>

namespace p1_ {

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
      std::pair<int, int> direction) {

    std::pair<int, int> check_loc = 
    { location.first + direction.first, location.second + direction.second };
    if (check_valid_direction(check_loc, { map.size(), map[0].size() } )) {
      if (map[check_loc.first][check_loc.second] == '#') {
        direction = _90deg_turn(direction);
        check_loc = location;
      } else {
        map[check_loc.first][check_loc.second] = 'X';
      }
      walk(map, check_loc, direction);
    } 
  }

}
