#include <cctype>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>

namespace p1_ {

  std::vector<std::pair<int,int>> full_paths = { 
    {0, 1}, {0, -1}, 
    {1, 1}, {1, 0}, {1, -1}, 
    {-1, 1}, {-1, 0}, {-1, -1}
  };

  std::vector<std::pair<int, int>> get_valid_directions(
      std::pair<int, int> location, 
      std::pair<int, int> dimensions) {

    int row = location.first;
    int col = location.second;
    int dim_r = dimensions.first;
    int dim_c = dimensions.second;
    std::vector<std::pair<int, int>> output;

    if (row == 0) {
      if (col == 0) {
        output = {{0, 1}, {1, 1}, {1, 0}};
        return output;
      }
      else if (col == dim_c) {
        output = {{0, -1}, {1, -1}, {1, 0}};
        return output;
      }
      else {
        output = {{0, -1}, {0, 1}, {1, -1}, {1, 1}, {1, 0}};
        return output;
      }
    }
    else if (row == dim_r) {
      if (col == 0) {
        output = {{0, 1}, {-1, 1}, {-1, 0}};
        return output;
      }
      else if (col == dim_c) {
        output = {{0, -1}, {-1, -1}, {-1, 0}};
        return output;
      }
      else {
        output = {{0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {-1, 0}};
        return output;
      }
    }
    else {
      if (col == 0) {
        output = {{0, 1}, {1, 1}, {1, 0}, {-1, 1}, {-1, 0}};
        return output;
      }
      else if (col == dim_c) {
        output = {{0, -1}, {1, -1}, {1, 0}, {-1, -1}, {-1, 0}};
        return output;
      }
      else {
        output = {{0, 1}, {0, -1}, {1, 1}, {1, 0}, {1, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
        return output;
      }
    }
    return output;
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


  bool check_A(
      std::pair<int, int> direction, 
      std::vector<std::vector<char>> map,
      std::pair<int, int> location) { 

    std::pair<int, int> check_loc = 
    { location.first + direction.first, location.second + direction.second };
    if (!check_valid_direction(check_loc, { map.size(), map[check_loc.first].size() })) { return false; }
    /* std::cout << check_loc.first << " " << check_loc.second << std::endl; */

    if (map[check_loc.first][check_loc.second] == 'S') {
      return true;
      /* std::cout << "-"; */
      /* return check_S(direction, map, check_loc); */
      /* std::cout << "M in direction: " << direction.first << " " << direction.second << std::endl; */
    }
    return false; 
  }
  bool check_M(
      std::pair<int, int> direction, 
      std::vector<std::vector<char>> map,
      std::pair<int, int> location) { 

    std::pair<int, int> check_loc = 
    { location.first + direction.first, location.second + direction.second };
    if (!check_valid_direction(check_loc, { map.size(), map[check_loc.first].size() })) { return false; }
    /* std::cout << check_loc.first << " " << check_loc.second << std::endl; */

    if (map[check_loc.first][check_loc.second] == 'A') {
      return check_A(direction, map, check_loc);
      /* std::cout << "M in direction: " << direction.first << " " << direction.second << std::endl; */
    }
    return false; 
  }
  bool check_X(
      std::pair<int, int> direction, 
      std::vector<std::vector<char>> map,
      std::pair<int, int> location) { 

    std::pair<int, int> check_loc = 
    { location.first + direction.first, location.second + direction.second };
    if (!check_valid_direction(check_loc, { map.size(), map[check_loc.first].size() })) { return false; }
    /* std::cout << check_loc.first << " " << check_loc.second << std::endl; */

    if (map[check_loc.first][check_loc.second] == 'M') {
      /* if (location.second == 5 && location.first == 0) {  */
      /*   std::cout << "CHECKING" << std::endl;  */
      /*   std::cout << direction.first << " " << direction.second << std::endl; */
      /*   std::cout << map[check_loc.first + direction.first][check_loc.second + direction.second] << std::endl; */
      /* } */
      /* std::cout << "-"; */
      return check_M(direction, map, check_loc);
      /* std::cout << "M in direction: " << direction.first << " " << direction.second << std::endl; */
    }
    return false; 
  }

}
