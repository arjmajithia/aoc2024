#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "machine.h"

#include "p1_utils.cpp"
#include "p2_utils.cpp"

int main() {
  /* std::string filename = "inputs/day13_1.txt"; */
  /* std::string filename = "inputs/tmp"; */
  std::string filename = "inputs/day13_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<Machine> machines;
  Machine machine;
  machine.clear();

  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      if(line.find_first_not_of(' ') != std::string::npos)
      {
        button btn;
        std::string vals = line.substr(line.find(":") + 2);
        std::string xVal = vals.substr(0, vals.find(","));
        std::string yVal = vals.substr(vals.find(","));
        auto xp = xVal.find("+");
        auto yp = yVal.find("+");
        if (xp != std::string::npos) {
          btn.x = std::stoll(xVal.substr(xp));
        } else {
          xp = xVal.find("=");
          btn.x = std::stoll(xVal.substr(xp+1));
        }

        if (yp != std::string::npos) {
          btn.y = std::stoll(yVal.substr(yp));
        } else {
          yp = yVal.find("=");
          btn.y = std::stoll(yVal.substr(yp+1));
        }
        if (machine.A.empty()) { machine.A = btn; }
        else if (machine.B.empty()) { machine.B = btn; }
        else if (machine.xX == 0 && machine.xY == 0) { 
          machine.xX = btn.x; 
          machine.xY = btn.y; 
        }
      }
      else {
        machines.push_back(machine);
        machine.clear();
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }
  machines.push_back(machine);
  machine.clear();

  int64_t total = 0;
  for (auto m : machines) {
    #ifdef PART1
      total += p1_::solve(m);
    #endif
    #ifndef PART1
      total += p2_::solve(m);
    #endif
  }

  std::cout << total << std::endl;

  return 0;
}
