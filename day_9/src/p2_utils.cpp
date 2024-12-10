#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace p2_ {

  /* bool vec_compare(const int64_t &begin, const int64_t &end) { */
  /*   return false; */
  /* } */

  void get_diskMap( 
      std::unordered_map<int64_t, std::vector<int64_t>> &disk_map,
      std::unordered_map<int64_t, int64_t> &map_sizes,
      std::vector<int64_t> blocks) {

    disk_map.clear();
    map_sizes.clear();
    for (int index = 0; index < blocks.size(); index++) {
      if (blocks[index] != -1) {
        disk_map[blocks[index]].push_back(index);
      }
    }
    for (auto d : disk_map) { 
      map_sizes[d.first] = d.second.size(); 
      std::sort(d.second.begin(), d.second.end(), std::greater<int64_t>());
    }
  }
  void get_negsMap( 
      std::unordered_map<int64_t, std::vector<int64_t>> &negs_map,
      std::unordered_map<int64_t, int64_t> &negs_sizes,
      std::vector<int64_t> blocks) {
    
    negs_sizes.clear();
    negs_map.clear();
    int64_t started = -1;
    for (int i = 0; i < blocks.size(); ++i) {
      if (blocks[i] != -1) {
        started = -1;
        continue;
      } else {
        if (started == -1) {
          started = i;
          negs_map[i].push_back(i);
        } else {
          negs_map[started].push_back(i);
        }
      }
    }
    for (auto n : negs_map) { 
      negs_sizes[n.first] = n.second.size(); 
    }
  }

  void move_(
      std::vector<int64_t> &blocks,
      std::vector<int64_t> order,
      std::unordered_map<int64_t, std::vector<int64_t>> &negs_map,
      std::unordered_map<int64_t, int64_t> &negs_sizes,
      std::unordered_map<int64_t, std::vector<int64_t>> &disk_map,
      std::unordered_map<int64_t, int64_t> &map_sizes) {

    for (int i = 0; i < order.size(); ++i) {
      int64_t current = order[i];
      int64_t current_size = map_sizes[current];
      int64_t replacement_index = std::numeric_limits<int64_t>::max();
      /* std::cout << "Current: " << current << " , Current Size: " << current_size << std::endl;  */
      for (auto n : negs_sizes) {
        if (n.second >= current_size) {
          if (n.first < replacement_index) { replacement_index = n.first; }
        }
      }
      /* std::cout << "Replacement Index: " << replacement_index << std::endl; */
      if (replacement_index > blocks.size()) { continue; }
      if (replacement_index > disk_map[current][0]) { continue; }
      for (int i = 0; i < current_size; i++) {
        /* std::cout << "swap " << i << std::endl; */
        std::iter_swap(blocks.begin() + disk_map[current][i], blocks.begin() + negs_map[replacement_index][0]);
        disk_map[current][i] = negs_map[replacement_index][0];
        /* std::cout << "swap to disk map done" << std::endl; */
        negs_map[replacement_index].erase(negs_map[replacement_index].begin());
        /* std::cout << "remove from neg map done" << std::endl; */
      }
      /* std::cout << "Replaced at: " << replacement_index << " now size " << negs_map[replacement_index].size() << std::endl; */
      /* for (auto n : negs_map) { negs_sizes[n.first] = n.second.size(); } */
      /* std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;; */
      /* std::cout << "Negs Map:" << std::endl;; */
      /* for (auto n : negs_map) {  */
      /*   std::cout << n.first << " has indices: "; */
      /*   for (auto v : n.second) { */
      /*     std::cout << v << " "; */
      /*   } */
      /*   std::cout << std::endl; */
      /* } */
      /* for (auto block : blocks) {  */
      /*   std::cout << block << " ";  */
      /* } */
      /* std::cout << std::endl; */
      get_diskMap(disk_map, map_sizes, blocks);
      get_negsMap(negs_map, negs_sizes, blocks);
    }
    /* for (auto block : blocks) {  */
    /*   std::cout << block << " ";  */
    /* } */
    /* std::cout << std::endl; */
  }

  int64_t get_total(std::vector<int64_t> blocks) {
    int64_t total = 0;
    for (int64_t i = 0; i < blocks.size(); ++i) {
      if (blocks[i] == -1) { continue; }
      else { total += (i * blocks[i]); }
      /* std::cout << i << " * " << blocks[i] << " | "; */
    }
    return total;
    /* std::cout << std::endl; */
  }

  int64_t move_and_calc( 
      std::vector<int64_t> &blocks,
      std::vector<int64_t> order,
      std::unordered_map<int64_t, std::vector<int64_t>> &negs_map,
      std::unordered_map<int64_t, int64_t> &negs_sizes,
      std::unordered_map<int64_t, std::vector<int64_t>> &disk_map,
      std::unordered_map<int64_t, int64_t> &map_sizes) {

    move_(blocks, order, negs_map, negs_sizes, disk_map, map_sizes);
    int64_t total = get_total(blocks);
    return total;
  }


}
