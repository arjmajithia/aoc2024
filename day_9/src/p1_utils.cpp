#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

namespace p1_ {

  void move_(std::vector<int64_t> &blocks) {
    int64_t mover = blocks.size() - 1;
    int64_t index = 0;
    while (true) {
      if (blocks[mover] == -1) { mover--; continue; }
      if (mover == 0) { break; }
      auto current = std::find(blocks.begin(), blocks.end(), -1);
      if (mover < std::distance(blocks.begin(), current)) { break; }
      std::iter_swap(blocks.begin() + mover, current);
      mover--;
      /* for (auto b : blocks) { std::cout << b << " "; } */
      /* std::cout << mover << " | "; */
      /* std::cout << std::distance(blocks.begin(), current)<< " "; */
      /* std::cout << std::endl; */
    }

    /* for (auto b : blocks) { */
    /*   std::cout << b << " "; */
    /* } */
    /* std::cout << std::endl; */

    auto first_neg = std::find(blocks.begin(), blocks.end(), -1);
    blocks.erase(first_neg, blocks.end());
  }

  int64_t get_total(std::vector<int64_t> blocks) {
    int64_t total = 0;
    for (int64_t i = 0; i < blocks.size(); ++i) {
      total += (i * blocks[i]);
      /* std::cout << i << " * " << blocks[i] << " | "; */
    }
    return total;
    /* std::cout << std::endl; */
  }

  int64_t move_and_calc(std::vector<int64_t> &blocks) {
    move_(blocks);
    int64_t total = get_total(blocks);
    return total;
  }

}
