#ifndef IVEX_IV_HPP
#define IVEX_IV_HPP

#include <vector>
#include <JoSIM/Input.hpp>

namespace ivex {

  typedef std::vector<std::pair<double, double>> iv_result;

  iv_result calculate_iv_curve(const double &limit, JoSIM::Input &input_object);

}

#endif