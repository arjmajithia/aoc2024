#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "coordinate.h"

#include "p1_utils.cpp"
#include "p2_utils.cpp"

std::map<char, std::pair<int, int>> c_direction = {
  {'^', {-1, 0}},
  {'>', {0, 1}},
  {'v', {1, 0}},
  {'<', {0, -1}}
};

bool isvalid(std::pair<int, int> c_l, std::pair<int, int> m_b) {
  return 
    c_l.first < m_b.first &&
    c_l.first > 0 &&
    c_l.second < m_b.second &&
    c_l.second > 0;
}

void print_boxes(
    std::vector<std::vector<int64_t>> imap,
    std::vector<std::vector<std::pair<box, int64_t>>> map,
    std::pair<int64_t, int64_t> mb,
    box cl) {

  bool cl_f = true;
  for (int64_t i = 0; i < mb.first; i++) {
    for (int64_t j = 0; j < mb.second; j++) {
      if (i == cl.first.x && j == cl.first.y) { std::cout << "@"; }
      if (i == cl.second.x && j == cl.second.y) { std::cout << "_"; }
      if (map[i][j].second == 1) { std::cout << "[]"; }
      if (map[i][j].second == 2) {  continue; }
      if (map[i][j].second == 0) { std::cout << ".."; }
      if (map[i][j].second == -1) { std::cout << "##"; }
    }
    std::cout << std::endl;
  }
}

int p2() {
  /* std::string filename = "inputs/day15_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/tmp3";
  /* std::string filename = "inputs/day15_1.prod"; */
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  bool reading_map = true;

  std::vector<std::pair<int64_t, int64_t>> movements;
  std::vector<std::vector<char>> c_map;
  std::vector<std::vector<int64_t>> imap;
  std::vector<std::vector<std::pair<box, int64_t>>> map;
  box current_location;

  int64_t row = 0;
  int64_t col = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> ln_map;
      if(line.find_first_not_of(' ') != std::string::npos)
      {
        if (reading_map) { 
          std::vector<int64_t> i_map;
          std::vector<std::pair<box, int64_t>> b_map;
          for (int64_t col = 0; col < line.length(); ++col) {
            char c = line[col];
            ln_map.push_back(c);
            if (c == '#') { 
              i_map.push_back(-1); i_map.push_back(-1); 
              coordinate f, s; f.x = row; f.x = row; s.y = col; s.y = col + 1;
              box box = {f, s};
              b_map.push_back({box, -1});
            }
            else if (c == 'O') { 
              i_map.push_back(1); i_map.push_back(1); 
              coordinate f, s; f.x = row; f.x = row; s.y = col; s.y = col + 1;
              box box = {f, s};
              b_map.push_back({box, 1});
            }
            else if (c == '@') { 
              i_map.push_back(2); i_map.push_back(2); 
              coordinate l, f; l.x = row; l.x = row; f.y = col; f.y = col + 1;
              current_location = std::make_pair(l, f); 
              b_map.push_back({current_location, 2});
            }
            else { 
              i_map.push_back(0); i_map.push_back(0);
              coordinate f, s; f.x = row; f.x = row; s.y = col; s.y = col + 1;
              box box = {f, s};
              b_map.push_back({box, 0});
            }
          }
          imap.push_back(i_map);
          map.push_back(b_map);
          col = line.length();
          row++;
        }
        else {
          for (int64_t i = 0; i < line.length(); ++i) {
            movements.push_back(c_direction[line[i]]);
          }
        }
      }
      else { reading_map = false; }
      if (!ln_map.empty()) { c_map.push_back(ln_map); }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  std::pair<int64_t, int64_t> map_bounds = std::make_pair(row, col);
  /* for (auto r : c_map) { */
  /*   for (auto c : r) { */
  /*     std::cout << c; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */

  std::vector<std::tuple<box, coordinate, int64_t>> changed;
  std::cout << row << std::endl;
  print_boxes(imap, map, map_bounds, current_location);
  std::cout << movements[0].first << " , " << movements[0].second << std::endl;
  bool ret = p2_::check_push(
      current_location, 
      current_location.first, 
      movements[0], 
      {0, 0}, 
      map_bounds,
      imap, 
      map, 
      changed);

  int64_t previous = map[current_location.first.x][current_location.first.y].second;
  for (auto c : changed) {
    previous = std::get<2>(c);;
    map[std::get<1>(c).x][std::get<1>(c).y] = { std::get<0>(c), std::get<2>(c) };
  }
  print_boxes(imap, map, map_bounds, current_location);

  /* for (int64_t i = 0; i < movements.size(); ++i) { */
  /*   int64_t previous_l = map[current_location.first.x][current_location.first.y]; */
  /*   int64_t previous_f = map[current_location.second.x][current_location.second.y]; */
  /*   if (p2_::check_push(current_location, movements[i], map_bounds, map, changed, previous)) { */
  /*     for (int64_t i = 0; i < map.size(); ++i) { */
  /*       for (int64_t j = 0; j < map[i].size(); ++j) { */
  /*         if (map[i][j] == 1) { std::cout << "O"; } */
  /*         if (map[i][j] == 2) { std::cout << "@"; } */
  /*         if (map[i][j] == 0) { std::cout << "."; } */
  /*         if (map[i][j] == -1) { std::cout << "#"; } */
  /*       } */
  /*       std::cout << std::endl; */
  /*     } */
  /*    */
  /*     for (auto c : changed) { */
  /*       previous = std::get<2>(c); */
  /*       map[std::get<0>(c)][std::get<1>(c)] = std::get<2>(c); */
  /*     } */
  /*    */
  /*     map[current_location.first][current_location.second] = 0; */
  /*    */
  /*     current_location = { */
  /*       current_location.first + movements[i].first,  */
  /*       current_location.second + movements[i].second}; */
  /*    */
  /*    */
  /*     changed.clear(); */
  /*   } */
  /* } */
  /* std::cout << current_location.first << ", " << current_location.second << std::endl; */

  int64_t total = 0;
  for (int64_t i = 0; i < map.size(); ++i) {
    for (int64_t j = 0; j < map[i].size(); ++j) {
      if (map[i][j].second == 1) {
        total += ((100 * i) + j);
      }
    }
  }

  std::cout << total << std::endl;

  return 0;

}

int p1() {
  /* std::string filename = "inputs/day15_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day15_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  bool reading_map = true;

  std::vector<std::pair<int64_t, int64_t>> movements;
  std::vector<std::vector<char>> c_map;
  std::vector<std::vector<int64_t>> map;
  std::pair<int64_t, int64_t> current_location;

  int64_t row = 0;
  int64_t col = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::vector<char> ln_map;
      if(line.find_first_not_of(' ') != std::string::npos)
      {
        if (reading_map) { 
          std::vector<int64_t> inv_map;
          for (int64_t col = 0; col < line.length(); ++col) {
            char c = line[col];
            ln_map.push_back(c);
            if (c == '#') { inv_map.push_back(-1); }
            else if (c == 'O') { inv_map.push_back(1); }
            else if (c == '@') { inv_map.push_back(2); current_location = std::make_pair(row, col); }
            else { inv_map.push_back(0); }
          }
          map.push_back(inv_map);
          col = line.length();
          row++;
        }
        else {
          for (int64_t i = 0; i < line.length(); ++i) {
            movements.push_back(c_direction[line[i]]);
          }
        }
      }
      else { reading_map = false; }
      if (!ln_map.empty()) { c_map.push_back(ln_map); }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  std::cout << row << std::endl;
  std::pair<int64_t, int64_t> map_bounds = std::make_pair(row, col);
  /* for (auto r : c_map) { */
  /*   for (auto c : r) { */
  /*     std::cout << c; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */

  std::cout << movements.size() << std::endl;
  std::cout << map_bounds.first << ", " << map_bounds.second << std::endl;
  std::cout << current_location.first << ", " << current_location.second << std::endl;
  std::vector<std::tuple<int64_t, int64_t, int64_t>> changed;

  for (int64_t i = 0; i < movements.size(); ++i) {
    int64_t previous = map[current_location.first][current_location.second];
    if (p1_::check_push(current_location, movements[i], map_bounds, map, changed, previous)) {
      /* for (int64_t i = 0; i < map.size(); ++i) { */
      /*   for (int64_t j = 0; j < map[i].size(); ++j) { */
      /*     if (map[i][j] == 1) { std::cout << "O"; } */
      /*     if (map[i][j] == 2) { std::cout << "@"; } */
      /*     if (map[i][j] == 0) { std::cout << "."; } */
      /*     if (map[i][j] == -1) { std::cout << "#"; } */
      /*   } */
      /*   std::cout << std::endl; */
      /* } */
    
      for (auto c : changed) {
        previous = std::get<2>(c);
        map[std::get<0>(c)][std::get<1>(c)] = std::get<2>(c);
      }
    
      map[current_location.first][current_location.second] = 0;
    
      current_location = {
        current_location.first + movements[i].first, 
        current_location.second + movements[i].second};
    
    
      changed.clear();
    }
  }
  for (int64_t i = 0; i < map.size(); ++i) {
    for (int64_t j = 0; j < map[i].size(); ++j) {
      if (map[i][j] == 1) { std::cout << "O"; }
      if (map[i][j] == 2) { std::cout << "@"; }
      if (map[i][j] == 0) { std::cout << "."; }
      if (map[i][j] == -1) { std::cout << "#"; }
    }
    std::cout << std::endl;
  }
  /* std::cout << current_location.first << ", " << current_location.second << std::endl; */

  int64_t total = 0;
  for (int64_t i = 0; i < map.size(); ++i) {
    for (int64_t j = 0; j < map[i].size(); ++j) {
      if (map[i][j] == 1) {
        total += ((100 * i) + j);
      }
    }
  }

  std::cout << total << std::endl;

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
