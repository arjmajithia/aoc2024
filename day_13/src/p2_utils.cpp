#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>

#include "machine.h"

namespace p2_ {

  int64_t add = 10000000000000;

  int64_t solve(Machine m) {
    m.xX = m.xX + add;
    m.xY = m.xY + add;
    int64_t total = 0;
    if ((m.A.x * m.B.y) == (m.B.x * m.A.y)) { return 0; }

    double num_a = ((m.xX * m.B.y) - (m.xY * m.B.x));
    double num_b = ((m.xY * m.A.x) - (m.xX * m.A.y));
    int64_t denom =  ((m.A.x * m.B.y) - (m.A.y * m.B.x));
    num_a = num_a / denom;
    num_b = num_b / denom;

    double intpart;
    if (std::modf(num_a, &intpart) == 0.0 && std::modf(num_b, &intpart) == 0.0) {
      total += ((num_a * 3) + num_b);
    }

    return total;
  }

}
