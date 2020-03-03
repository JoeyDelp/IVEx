#include <iostream>
#include "ivex/Input.hpp"
#include "JoSIM/Matrix.hpp"
#include "JoSIM/Simulation.hpp"

void version_info() {
  std::cout << "IVEx - JJ Current/Voltage Characteristics Extraction Tool" << std::endl;
  std::cout << "Copyright (C) 2020 by QCS (joeydelp@gmail.com)" << std::endl;
  std::cout << "v" << VERSION << "." << GIT_COMMIT_HASH << " compiled on " << __DATE__ << " at "
            << __TIME__ << std::endl;
  std::cout << std::endl;
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
    // If not a datafile
    if(!ivars.datafile_name) {
      ivex::parse_model(input_object, ivars);
      ivex::setup_transsim(input_object);
      for (int i = 1; i <= 400; ++i) {
        input_object.netlist.maindesign.clear();
        input_object.netlist.expNetlist.clear();
        ivex::create_standard_netlist(input_object, std::to_string(static_cast<double>(i) * 25E-7));
        std::cout.rdbuf(buffer.rdbuf());
        JoSIM::Matrix matrix_object;
        matrix_object.create_matrix(input_object);
        JoSIM::Simulation simulation_object(input_object, matrix_object);
      }
    } else {
      // Extract model

    }
  } catch (std::runtime_error &e) {
    std::cout.rdbuf(cout_buff);
    std::cout << e.what() << std::endl;
    exit(-1);
  }
}