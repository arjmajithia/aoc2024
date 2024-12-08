#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

namespace p1_ {

  bool check_valid_tennas(
      std::pair<int, int> check_location, 
      std::pair<int, int> dimensions) {

    if (check_location.first > dimensions.first) {
      return false;
    } else if (check_location.first < 0) {
      return false;
    }
    if (check_location.second > dimensions.second) {
      return false;
    } else if (check_location.second < 0) {
      return false;
    }
    return true;
  }

  void get_comp(std::pair<int, int> first, std::pair<int, int> second, std::pair<int, int> dimensions,
      std::vector<std::pair<int, int>> &locations) {
    std::pair<int, int> difference = {first.first - second.first, first.second - second.second};
    std::pair<int, int> new_lhs = {first.first + difference.first, first.second + difference.second};
    std::pair<int, int> new_rhs = {second.first - difference.first, second.second - difference.second};
    /* std::cout << new_lhs.first << "," << new_lhs.second << " , "; */
    /* std::cout << new_rhs.first << "," << new_rhs.second << ": "; */
    /* std::cout << check_valid_tennas(new_lhs, dimensions) << " , " << check_valid_tennas(new_rhs, dimensions) << " | "; */
    /* std::cout << std::endl; */

    if (check_valid_tennas(new_lhs, dimensions)) { 
      if (std::find(locations.begin(), locations.end(), new_lhs) == locations.end()) {
        locations.push_back(new_lhs); 
      }
    }
    if (check_valid_tennas(new_rhs, dimensions)) { 
      if (std::find(locations.begin(), locations.end(), new_rhs) == locations.end()) {
        locations.push_back(new_rhs); 
      }
    }
  }

  int get_antennas(std::vector<std::pair<int, int>> location, std::pair<int, int> dimensions, 
      std::vector<std::pair<int, int>> &locations) {
    int out = 0;
    for (int first = 0; first < location.size(); first++) {
      for (int second = first + 1; second < location.size(); second++) {
        if (location[first] == location[second]) { continue; }
        /* std::cout << location[first].first << "," << location[first].second << " -> "; */
        /* std::cout << location[second].first << "," << location[second].second << "; "; */
        get_comp(location[first], location[second], dimensions, locations);
      }
    }
    return out;
  }

}
