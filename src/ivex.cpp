#include <iostream>
#include "ivex/Input.hpp"

void version_info() {
  std::cout << "IVEx - JJ Current/Voltage Characteristics Extraction Tool" << std::endl;
  std::cout << "Copyright (C) 2020 by QCS (joeydelp@gmail.com)" << std::endl;
  std::cout << "v" << VERSION << "." << GIT_COMMIT_HASH << " compiled on " << __DATE__ << " at "
            << __TIME__ << std::endl;
  std::cout << std::endl;
}

int main(int argc, const char **argv) {
  version_info();
  try {
    ivex::ivex_vars ivars;
    // Read in sysargs and determine mode as model or data
    JoSIM::Input input_object;
    ivex::input_parse(argc, argv, ivars);
    // If not a datafile
    if(!ivars.datafile) {
      // Simulate the identified model
    } else {
      // Extract model

    }
  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
    exit(-1);
  }
}