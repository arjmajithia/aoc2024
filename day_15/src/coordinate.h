#pragma once

#include <cstdint>
#include <utility>

struct coordinate {
  int64_t x;
  int64_t y;
};

typedef std::pair<coordinate, coordinate> box;
