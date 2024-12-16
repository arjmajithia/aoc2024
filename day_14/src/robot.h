#include <cstdint>
#include <iostream>
#include <utility>

struct Robot {
  std::pair<int64_t, int64_t> location;
  std::pair<int64_t, int64_t> direction;

  void print() {
    std::cout << "Location: (" << location.first << ", " << location.second << ") ";
    std::cout << "Direction (" << direction.first << ", " << direction.second << ")";
    std::cout << std::endl;
  }

  void move_X(std::pair<int64_t, int64_t> limits, int64_t X) {
    auto xdirect = X * direction.first;
    auto ydirect = X * direction.second;

    std::pair<int64_t, int64_t> check_location = {
      location.first + xdirect,
      location.second + ydirect
    };
    check_location.first = ((check_location.first % limits.first) + limits.first) % limits.first;
    check_location.second = ((check_location.second % limits.second) + limits.second) % limits.second;
    location = check_location;
  }

  int get_quadrant(std::pair<int64_t, int64_t> quad_limits) {
    int out = 0;
    if (location.second == quad_limits.second) { return out; }
    if (location.first == quad_limits.first) { return out; }

    if (location.second < quad_limits.second 
        && location.first < quad_limits.first) {
      out = 1;
    }
    if (location.second < quad_limits.second 
        && location.first > quad_limits.first) {
      out = 2;
    }
    if (location.second > quad_limits.second 
        && location.first < quad_limits.first) {
      out = 3;
    }
    if (location.second > quad_limits.second 
        && location.first > quad_limits.first) {
      out = 4;
    }

    return out;
  }

  std::pair<int64_t, int64_t> steps(std::pair<int64_t, int64_t> limits, int64_t X) {
    auto xdirect = X * direction.first;
    auto ydirect = X * direction.second;

    std::pair<int64_t, int64_t> check_location = {
      location.first + xdirect,
      location.second + ydirect
    };
    check_location.first = ((check_location.first % limits.first) + limits.first) % limits.first;
    check_location.second = ((check_location.second % limits.second) + limits.second) % limits.second;

    return check_location;
  }

};
