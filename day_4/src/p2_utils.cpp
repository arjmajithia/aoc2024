#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace p2_ {
  /* std::vector<std::pair<int,int>> full_paths = {  */
  /*   {1, -1}, {1, 1}, */
  /*   {-1, -1}, {-1, 1} */
  /* }; */
  std::vector<std::pair<int, int>> check_paths = {
    {1, -1}, {1, 1}
  };

  std::unordered_map<std::string, std::pair<int,int>> path_swap( {
      { "1, -1", {-1, 1,}, },
      { "1, 1", {-1, -1,}, },
      /* { "-1, 1", {1, -1,}, }, */
      /* { "-1, -1", {1, 1,}, }, */
      });

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

  bool check_MorS(
      std::pair<int, int> direction, 
      std::vector<std::vector<char>> map,
      std::pair<int, int> location,
      bool mORs
      ) { 

    std::string map_key = std::to_string(direction.first) + ", " + std::to_string(direction.second);
    std::pair<int, int> rdirection = path_swap[map_key];
    std::pair<int, int> check_loc = 
      { location.first + rdirection.first, location.second + rdirection.second };
    if (!check_valid_direction(check_loc, { map.size(), map[check_loc.first].size() })) { return false; }

    if (mORs) {
      if (map[check_loc.first][check_loc.second] == 'S') {
        return true;
      }
    }
    else {
      if (map[check_loc.first][check_loc.second] == 'M') {
        return true;
      }
    }
    return false; 
  }

  bool check_A(
      std::pair<int, int> path,
      std::pair<int, int> location,
      std::vector<std::vector<char>> map) {

    std::pair<int, int> check_loc = 
      { location.first + path.first, location.second + path.second };
    if (map[check_loc.first][check_loc.second] == 'M') {
      return check_MorS(path, map, location, true);
    }
    if (map[check_loc.first][check_loc.second] == 'S') {
      return check_MorS(path, map, location, false);
    }
    return false;
  }

  bool on_A(
      std::pair<int, int> location,
      std::vector<std::vector<char>> map) {

    if (location.first == 0) { return false; }
    else if (location.first == map.size()-1) { return false; }
    if (location.second == 0) { return false; }
    else if (location.second == map[location.first].size()-1) { return false; }

    bool a_0 = check_A(check_paths[0], location, map);
    bool a_1 = check_A(check_paths[1], location, map);

    return check_A(check_paths[0], location, map) && check_A(check_paths[1], location, map);
  }

}
