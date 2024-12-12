#include <cmath>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace p1_ {

  std::pair<std::vector<int64_t>, std::vector<std::string>> check(
      std::vector<int64_t> num_line,
      std::vector<std::string> str_line,
      std::vector<int64_t> out_nline,
      std::vector<std::string> out_sline) {

    for (int64_t i = 0; i < num_line.size(); ++i) {
      int64_t curr_nval = num_line[i];
      std::string curr_sval = str_line[i];
      if (curr_nval == 0) {
        out_nline.push_back(1);
        out_sline.push_back("1");
        continue;
      }
      if (curr_sval.length() % 2 == 0) {
        std::string p1 = curr_sval.substr(0, curr_sval.length() / 2);
        std::string p2 = curr_sval.substr(curr_sval.length() / 2);
        out_nline.push_back(std::stoll(p1)); out_nline.push_back(std::stoll(p2));
        p1.erase(0, p1.find_first_not_of('0')); p2.erase(0, p2.find_first_not_of('0'));
        out_sline.push_back(p1); out_sline.push_back(p2);
        continue;
      }
      int64_t out_nval = curr_nval * 2024;
      out_nline.push_back(out_nval);
      out_sline.push_back(std::to_string(out_nval));
    }
    return {out_nline, out_sline};
  }

}
