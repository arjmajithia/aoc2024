#pragma once

#include <cstdint>
#include <iostream>

struct button {
  int64_t x;
  int64_t y;

  void clear() { x = 0; y = 0; }

  bool empty() {
    return x == 0 && y == 0;
  }
};

struct Machine {
  button A;
  button B;
  int64_t xX = 0;
  int64_t xY = 0;

  void clear() {
    A.clear(); 
    B.clear(); 
    xX = 0; xY = 0;
  }

  void print() {
    std::cout << "A: " << A.x << ", " << A.y << std::endl;
    std::cout << "B: " << B.x << ", " << B.y << std::endl;
    std::cout << "X: " << xX << ", " << xY << std::endl;
  }
};
