#ifndef IVEX_OUTPUT_HPP
#define IVEX_OUTPUT_HPP
#include <vector>
#include <fstream>
#include "./Input.hpp"
#include "./IV.hpp"

namespace ivex {

  void write_iv_curve(const ivex::ivex_vars &ivars, const ivex::iv_data &iv_result, std::optional<ivex::iv_data> iv_measured = std::nullopt);

  void write_model_to_file(const ivex::ivex_vars &ivars, const std::string &model_string);

}

#endif