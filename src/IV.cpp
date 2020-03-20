#include "ivex/IV.hpp"
#include "ivex/Input.hpp"
#include <JoSIM/Matrix.hpp>
#include <JoSIM/Simulation.hpp>
#include <numeric>

double avg_voltage(std::vector<double> const& v) {
    return std::accumulate(v.begin() + (3*(v.size()/4)), v.end(), 0.0) / (static_cast<double>(v.size())/4);
}

ivex::iv_data ivex::calculate_iv_curve(const double &limit, JoSIM::Input &input_object) {
  int steps = round(limit/5E-7);
  double current_start = 0.0, current_stop = 0.0;
  ivex::iv_data iv_res;
  iv_res.reserve(steps * 4);
  #pragma omp parallel for
  for (int i = 0; i < steps * 4; ++i) {
    input_object.netlist.maindesign.clear();
    input_object.netlist.expNetlist.clear();
    ivex::create_standard_netlist(input_object, std::to_string(current_start), std::to_string(current_stop));
    JoSIM::Matrix matrix_object;
    matrix_object.create_matrix(input_object);
    JoSIM::Simulation simulation_object(input_object, matrix_object);
    iv_res[i] = std::make_pair(avg_voltage(simulation_object.results.xVector.at(0).value()), current_stop);
    if ((i >= 0 && i < steps) || (i > steps * 3 && i < steps * 4)) {
      current_stop += 5E-7;
    } else if (i == steps || i == 3 * steps) {
      current_start = current_stop;
    } else if (i > steps && i < steps * 3) {
      current_stop -= 5E-7;
    }
  }
  return std::move(iv_res);
}