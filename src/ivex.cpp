#include <iostream>
#include "ivex/Input.hpp"
#include "ivex/Output.hpp"
#include "ivex/IV.hpp"

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
    if (ivex::input_parse(argc, argv, ivars) != 1) exit(-1);
    JoSIM::Input input_object;
    ivex::iv_result iv_res;
    // If not a datafile
    if(!ivars.datafile_name) {
      // Generate IV curve
      ivex::parse_model(input_object, ivars);
      ivex::setup_transsim(input_object);
      std::cout.rdbuf(buffer.rdbuf());
      iv_res = ivex::calculate_iv_curve(ivars.current_limit, input_object);
      ivex::write_iv_curve(ivars, iv_res);
    } else {
      // Extract model

    }
  } catch (std::runtime_error &e) {
    std::cout.rdbuf(cout_buff);
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  exit(0);
}