#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool is_number(std::string s) {
  return !s.empty() && std::find_if(s.begin(), s.end(), 
      [](unsigned char c){ return !std::isdigit(c); }) == s.end();
}

int p2() {
  /* std::string filename = "inputs/day1_2.txt"; */
  std::string filename = "inputs/day1_2.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::string> valid_;

  int line_num = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      bool do_ = true;
      std::string str_value;
      std::string int_value;
      bool int_val = false;
      bool first_val = false;
      for (int i = 0; i < line.length(); i++) {
        char c = line[i];
        /* std::cout << str_value << std::endl; */
        if (str_value.find("do()") != std::string::npos && str_value.find("don't()") == std::string::npos) { // prob better way of doing this, idgaf
          str_value.clear();
          do_ = true;
        }
        if (str_value.find("do()") == std::string::npos && str_value.find("don't()") != std::string::npos) {
          str_value.clear();
          do_ = false;
        }
        if (do_) {
          if (str_value == "mul" && c != '(') { str_value.clear(); }
          if (c == 'm') {
            str_value.clear();
            int_value.clear();
          }
          if (c == '(' && str_value == "mul") {
            str_value += c;
            int_val = true;
            /* std::cout << "str val: " << str_value << std::endl; */
          }
          if (c == ',' || c == ')') {
            if (is_number(int_value)) {
              if (!first_val && str_value.find("mul") == std::string::npos) {
                str_value.clear();
                continue;
              }
              /* std::cout << "pushing int val: " << int_value << std::endl; */
              /* std::cout << "___str val: " << str_value << std::endl; */
              valid_.push_back(int_value);
              int_value.clear();

              if (first_val) { first_val = false; }
              else { first_val = true; }

              str_value.clear();
              continue;
            }
            if (c == ')') {
              str_value += c;
              if (str_value.find("do()") != std::string::npos && str_value.find("don't()") == std::string::npos) { // prob better way of doing this, idgaf
                str_value.clear();
                do_ = true;
              }
              if (str_value.find("do()") == std::string::npos && str_value.find("don't()") != std::string::npos) {
                str_value.clear();
                do_ = false;
              }
              str_value.clear();
            }
            int_value = false;
            continue;
          }

          if (int_val && c != '(' && c != ')') {
            if (isdigit(c)) {
              int_value += c;
              /* std::cout << "int val: " << int_value << std::endl; */
            }        
            else {
              if (int_value.size() > 0 && valid_.size() > 0 && first_val) {
                /* std::cout << "pinged val: " << int_value << " on " << c << std::endl; */
                valid_.pop_back();
                first_val = false;
              }
              int_value.clear();
            }
          }
        }
        str_value += c;
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  if (valid_.size() % 2 != 0) {
    std::cout << "Valid vector is not of even size. Something went wrong" << std::endl;
    std::cout << valid_.size() << std::endl;
    for (auto c : valid_) {
      std::cout << c << " ";
    }
    std::cout << std::endl;
    return 1;
  }

  int total = 0;

  for (int i = 0; i < valid_.size(); i+=2) {
    int v1 = std::atoi(valid_[i].c_str());
    int v2 = std::atoi(valid_[i+1].c_str());
    total += v1 * v2;
    std::cout << valid_[i] << "*" << valid_[i+1] << std::endl;
  }

  std::cout << "total: " << total << std::endl;

  return 0;
}

int p1() {
  /* std::string filename = "inputs/day1_1.txt"; */
  std::string filename = "inputs/day1_1.prod";
  std::fstream input_file(filename.c_str(), std::ios::in | std::ios::out);
  if (!input_file) {
    std::cerr << "Error opening file\n";
  }

  std::cout << "Loaded file\n";
  std::string line;
  std::vector<std::string> valid_;

  int line_num = 0;
  if (input_file.is_open()) {
    while(std::getline(input_file, line))
    {
      std::string str_value;
      std::string int_value;
      bool int_val = false;
      bool first_val = false;
      for (int i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (str_value == "mul" && c != '(') { str_value.clear(); }
        if (c == 'm') {
          str_value.clear();
          int_value.clear();
        }
        if (c == '(' && str_value == "mul") {
          str_value += c;
          int_val = true;
          /* std::cout << "str val: " << str_value << std::endl; */
        }
        if (c == ',' || c == ')') {
          if (is_number(int_value)) {
            if (!first_val && str_value.find("mul") == std::string::npos) {
              str_value.clear();
              continue;
            }
            /* std::cout << "pushing int val: " << int_value << std::endl; */
            /* std::cout << "___str val: " << str_value << std::endl; */
            valid_.push_back(int_value);
            int_value.clear();

            if (first_val) { first_val = false; }
            else { first_val = true; }

            str_value.clear();
            continue;
          }
          if (c == ')') {
            str_value.clear();
          }
          int_value = false;
          continue;
        }

        if (int_val && c != '(' && c != ')') {
          if (isdigit(c)) {
            int_value += c;
            /* std::cout << "int val: " << int_value << std::endl; */
          }        
          else {
            if (int_value.size() > 0 && valid_.size() > 0 && first_val) {
              /* std::cout << "pinged val: " << int_value << " on " << c << std::endl; */
              valid_.pop_back();
              first_val = false;
            }
            int_value.clear();
          }
        }
        str_value += c;
      }
    }
    input_file.close();
  }
  else {
    std::cout << "file is closed\n";
  }

  if (valid_.size() % 2 != 0) {
    std::cout << "Valid vector is not of even size. Something went wrong" << std::endl;
    std::cout << valid_.size() << std::endl;
    for (auto c : valid_) {
      std::cout << c << " ";
    }
    std::cout << std::endl;
    return 1;
  }

  int total = 0;

  for (int i = 0; i < valid_.size(); i+=2) {
    int v1 = std::atoi(valid_[i].c_str());
    int v2 = std::atoi(valid_[i+1].c_str());
    total += v1 * v2;
    /* std::cout << valid_[i] << "*" << valid_[i+1] << std::endl; */
  }

  std::cout << "total: " << total << std::endl;

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
