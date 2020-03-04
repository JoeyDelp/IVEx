#include <iostream>
#include <numeric>
#include "ivex/Input.hpp"
#include "ivex/Output.hpp"
#include "JoSIM/Matrix.hpp"
#include "JoSIM/Simulation.hpp"

void version_info() {
  std::cout << "IVEx - JJ Current/Voltage Characteristics Extraction Tool" << std::endl;
  std::cout << "Copyright (C) 2020 by QCS (joeydelp@gmail.com)" << std::endl;
  std::cout << "v" << VERSION << "." << GIT_COMMIT_HASH << " compiled on " << __DATE__ << " at "
            << __TIME__ << std::endl;
  std::cout << std::endl;
}

double avg_voltage(std::vector<double> const& v) {
    return std::accumulate(v.begin() + (v.size()/2), v.end(), 0.0) / (static_cast<double>(v.size())/2);
}

int main(int argc, const char **argv) {
  version_info();
  std::streambuf* cout_buff = std::cout.rdbuf(); 
  std::stringstream buffer;
  try {
    ivex::ivex_vars ivars;
    // Read in sysargs and determine mode as model or data
    ivex::input_parse(argc, argv, ivars);
    JoSIM::Input input_object;
    int steps = 100;
    std::vector<std::pair<double, double>> iv_result;
    // If not a datafile
    if(!ivars.datafile_name) {
      ivex::parse_model(input_object, ivars);
      ivex::setup_transsim(input_object);
      double current_start = 0.0, current_stop = 0.0;
      for (int i = 0; i < steps; ++i) {
        input_object.netlist.maindesign.clear();
        input_object.netlist.expNetlist.clear();
        ivex::create_standard_netlist(input_object, std::to_string(current_start), std::to_string(current_stop));
        std::cout.rdbuf(buffer.rdbuf());
        JoSIM::Matrix matrix_object;
        matrix_object.create_matrix(input_object);
        JoSIM::Simulation simulation_object(input_object, matrix_object);
        iv_result.emplace_back(std::make_pair(current_stop, avg_voltage(simulation_object.results.xVector.at(0).value())));
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
        iv_result.emplace_back(std::make_pair(current_stop, avg_voltage(simulation_object.results.xVector.at(0).value())));
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
        iv_result.emplace_back(std::make_pair(current_stop, avg_voltage(simulation_object.results.xVector.at(0).value())));
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
        iv_result.emplace_back(std::make_pair(current_stop, avg_voltage(simulation_object.results.xVector.at(0).value())));
        current_stop += 25E-7;
      }
      ivex::write_iv_curve(ivars, iv_result);
    } else {
      // Extract model

    }
  } catch (std::runtime_error &e) {
    std::cout.rdbuf(cout_buff);
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  return 0;
}