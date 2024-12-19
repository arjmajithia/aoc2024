#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "p1_utils.cpp"
#include "p2_utils.cpp"

typedef std::pair<std::pair<int64_t, int64_t>, int64_t> s_loc;

std::map<int, std::pair<int64_t, int64_t>> directions = {
  {0, {0, 1}}, {1, {1, 0}}, {2, {0, -1}}, {3, {-1, 0}}
};

struct loc {
  int64_t cost;
  std::pair<int64_t, int64_t> location;
  int64_t direction; 

  loc(int64_t c_, std::pair<int64_t, int64_t> loc_, int64_t dir_) 
    : cost(c_), location(loc_), direction(dir_) {}

  bool operator>(const loc& other) const { return cost > other.cost; }
  bool operator<(const loc& other) const { return cost < other.cost; }
};

bool valid_loc(
    std::pair<int64_t, int64_t> location, 
    std::pair<int64_t, int64_t> bounds) {
  return location.first >= 0 && 
    location.second >= 0 && 
    location.first < bounds.first && 
    location.second < bounds.second;
}

void dijkstra(
    const std::vector<std::string> map,
    const std::vector<loc> &starting,
    std::map<std::pair<std::pair<int64_t, int64_t>, int64_t>, int64_t> best,
    std::pair<int64_t, int64_t> mbounds) {

  std::priority_queue<loc, std::vector<loc>> prioq;
  for (loc l : starting) { prioq.push(l); }
  while (!prioq.empty()) {
    loc current = prioq.top(); prioq.pop();
    s_loc l_c = std::make_pair(current.location, current.direction);

    if (best.count(l_c) && 
        current.cost >= best[l_c]) { 
      continue; 
    }
    best[l_c] = current.cost;
    std::pair<int64_t, int64_t> n_dir = directions[current.direction];
    std::pair<int64_t, int64_t> check_loc = {
      current.location.first + n_dir.first,
      current.location.second + n_dir.second
    };
    if (!valid_loc(check_loc, mbounds)) { continue; }

    if (map[check_loc.first][check_loc.second] == '.') {
      prioq.push(loc(current.cost + 1, check_loc, current.direction));
    }
    // rotate 90 degrees
    prioq.push(loc(current.cost + 1000, current.location, (current.direction + 1) % 4));
    // rotate 270 degrees
    prioq.push(loc(current.cost + 1000, current.location, (current.direction + 3) % 4));
  }
}

int p2() {
  return 0;
}

int p1() {
  std::string filename = "inputs/day16_1.txt";
  /* std::string filename = "inputs/tmp"; */
  /* std::string filename = "inputs/day16_1.prod"; */
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::string> map;
  std::pair<int64_t, int64_t> start;
  std::pair<int64_t, int64_t> end;

  int64_t row;
  int64_t col;
  if (input_file.is_open()) {
    while(std::getline(input_file, line)) { 
      for (auto c : line) {
        if (c == 'S') { start = {row, col}; }
        if (c == 'E') { start = {row, col}; }
        col++;
      }
      map.push_back(line); 
      row++;
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  std::pair<int64_t, int64_t> map_bounds = std::make_pair(row, col);

  for (int64_t i = 0; i < map.size(); ++i) {
    for (int64_t j = 0; j < map[i].size(); ++j) {
      if (std::make_pair(i, j) == start || std::make_pair(i, j) == end) { map[i][j] = '.'; }
    }
  }

  // Starting from S
  std::map<std::pair<std::pair<int64_t, int64_t>, int64_t>, int64_t> starting_best;
  std::vector<loc> starts;
  loc s_ = loc(0, start, 0);
  starts.push_back(s_);
  dijkstra(map, starts, starting_best, map_bounds);
  
  // initialize starts with all directions
  starts.clear();
  for (int i = 0; i < 4; ++i) {
    starts.push_back(loc(0, end,i));
  }
  
  // Starting from E
  std::map<std::pair<std::pair<int64_t, int64_t>, int64_t>, int64_t> ending_best;
  dijkstra(map, starts, ending_best, map_bounds);
  
  int64_t goal = std::numeric_limits<int64_t>::max();
  for (int i = 0; i < 4; ++i) {
    if (starting_best.count(std::make_pair(end, i))) { goal = std::min(goal, starting_best[{end, i}]); }
  }
  std::cout << "Goal: " << goal << std::endl;
  
  std::set<std::pair<int, int>> solutions;
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      for (int k = 0; k < 4; ++k) {
        s_loc start_key = std::make_pair(std::make_pair(i, j), k);
        s_loc end_key = std::make_pair(std::make_pair(i, j), (k + 2) % 4);
        if (!starting_best.count(start_key) || !ending_best.count(end_key)) { continue; }
        if (starting_best.count(start_key) + ending_best.count(end_key) == goal) { 
          solutions.insert({i, j});
        }
      }
    }
  }
  
  std::cout << solutions.size() << std::endl;

  return 0;
}

int main() {
#ifdef PART1
  p1();
#endif
#ifndef PART1
  p2();
#endif
}
