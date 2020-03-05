#include "ivex/IV.hpp"
#include "ivex/Input.hpp"
#include <JoSIM/Matrix.hpp>
#include <JoSIM/Simulation.hpp>
#include <numeric>

double avg_voltage(std::vector<double> const& v) {
    return std::accumulate(v.begin() + (v.size()/2), v.end(), 0.0) / (static_cast<double>(v.size())/2);
}

ivex::iv_result ivex::calculate_iv_curve(const double &limit, JoSIM::Input &input_object) {
  int steps = ceil(limit/25E-7);
  double current_start = 0.0, current_stop = 0.0;
  ivex::iv_result iv_res;
  for (int i = 0; i < steps; ++i) {
    input_object.netlist.maindesign.clear();
    input_object.netlist.expNetlist.clear();
    ivex::create_standard_netlist(input_object, std::to_string(current_start), std::to_string(current_stop));
    JoSIM::Matrix matrix_object;
    matrix_object.create_matrix(input_object);
    JoSIM::Simulation simulation_object(input_object, matrix_object);
    iv_res.emplace_back(std::make_pair(avg_voltage(simulation_object.results.xVector.at(0).value()), current_stop));
    current_stop += 25E-7;
  }
  current_start = current_stop;
  for (int i = steps; i >= 0; --i) {
    input_object.netlist.maindesign.clear();
    input_object.netlist.expNetlist.clear();
    ivex::create_standard_netlist(input_object, std::to_string(current_start), std::to_string(current_stop));
    JoSIM::Matrix matrix_object;
    matrix_object.create_matrix(input_object);
    JoSIM::Simulation simulation_object(input_object, matrix_object);
    iv_res.emplace_back(std::make_pair(avg_voltage(simulation_object.results.xVector.at(0).value()), current_stop));
    current_stop -= 25E-7;
  }
  current_start = current_stop;
  for (int i = 0; i < steps; ++i) {
    input_object.netlist.maindesign.clear();
    input_object.netlist.expNetlist.clear();
    ivex::create_standard_netlist(input_object, std::to_string(current_start), std::to_string(current_stop));
    JoSIM::Matrix matrix_object;
    matrix_object.create_matrix(input_object);
    JoSIM::Simulation simulation_object(input_object, matrix_object);
    iv_res.emplace_back(std::make_pair(avg_voltage(simulation_object.results.xVector.at(0).value()), current_stop));
    current_stop -= 25E-7;
  }
  current_start = current_stop;
  for (int i = steps; i >= 0; --i) {
    input_object.netlist.maindesign.clear();
    input_object.netlist.expNetlist.clear();
    ivex::create_standard_netlist(input_object, std::to_string(current_start), std::to_string(current_stop));
    JoSIM::Matrix matrix_object;
    matrix_object.create_matrix(input_object);
    JoSIM::Simulation simulation_object(input_object, matrix_object);
    iv_res.emplace_back(std::make_pair(avg_voltage(simulation_object.results.xVector.at(0).value()), current_stop));
    current_stop += 25E-7;
  }
  return std::move(iv_res);
}