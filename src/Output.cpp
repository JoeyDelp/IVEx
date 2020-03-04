#include "ivex/Output.hpp"

void ivex::write_iv_curve(const ivex::ivex_vars &ivars, const std::vector<std::pair<double, double>> &iv_result) {
  std::ofstream outfile(ivars.outputfile_name.value());
  if (outfile.is_open()) {
    for (auto i : iv_result) {
      outfile << i.first << "," << i.second << std::endl;
    }
    outfile.close();
  }
}