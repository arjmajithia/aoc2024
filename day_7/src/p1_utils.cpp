#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace p1_ {
  bool can_make(int64_t value, std::vector<int64_t> options) {
    if (options.size() == 1) { return value == options[0]; }
    int64_t last = options[options.size() - 1];
    std::vector<int64_t> noptions = options;
    noptions.pop_back();

    bool possible_mul = false;
    if (value % last == 0) {
      int64_t div_val = std::floor(value/last);
      possible_mul = can_make(div_val, noptions);
    }

    bool possible_add = can_make(value - last, noptions);

    return (possible_mul || possible_add);
  }
}
