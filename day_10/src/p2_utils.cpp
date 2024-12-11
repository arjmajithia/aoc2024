#include <array>
#include <utility>
#include <vector>

namespace p2_ {
  std::array<std::pair<int, int>, 4> directions = {
    {{-1, 0},
      {1, 0},
      {0, -1},
      {0, 1}}
  };

  bool valid_location(
      std::pair<int, int> dimensions, 
      std::pair<int, int> location) {
    return location.first >= 0 && 
      location.second >= 0 && 
      location.first < dimensions.first && 
      location.second < dimensions.second;
  }

  int walk(
      std::vector<std::vector<int>> map,
      std::pair<int, int> dimensions,
      std::pair<int, int> location) {

    if (map[location.first][location.second] == 9) {
      return 1;
    }
    int sum = 0;

    for (std::pair<int, int> direction : directions) {
      std::pair<int, int> check_loc = 
        std::make_pair(location.first + direction.first, location.second + direction.second);
      if (!valid_location(dimensions, check_loc)) { continue; }
      if (map[check_loc.first][check_loc.second] == map[location.first][location.second] + 1) {
        sum += walk(map, dimensions, check_loc);
      }
    }
    return sum;
  }

}
