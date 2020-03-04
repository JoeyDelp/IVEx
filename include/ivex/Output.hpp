#ifndef IVEX_OUTPUT_HPP
#define IVEX_OUTPUT_HPP
#include <vector>
#include <fstream>
#include "./Input.hpp"

namespace ivex {

  void write_iv_curve(const ivex::ivex_vars &ivars, const std::vector<std::pair<double, double>> &iv_result);

}

#endif