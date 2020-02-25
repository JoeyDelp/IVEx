#include "ivex/Input.hpp"
#include <iostream>
#include <fstream>
#include <optional>

using namespace ivex;

// Local function prototypes
std::string missing_arguments();
std::string bad_arguments();
void display_help();

void ivex::input_parse(int argc, const char **argv, ivex_vars &ivars){
  // Complain if there are no arguments
  if (argc <= 1) {
    throw std::runtime_error(missing_arguments());
  } else {
    // Parse each input argument
    for (int i = 1; i < argc; ++i) {
      // Ensure argument has more than one character
      if(sizeof(argv[i]) > 1) {
        // If '-'
        if (argv[i][0] == '-') {
          // If '-d'
          if (argv[i][1] == 'd') {
            ivars.datafile = true;
          // If '-h'
          } else if (argv[i][1] == 'h') {
            display_help();
          // If '--'
          } else if (argv[i][1] == '-') {
            if(sizeof(argv[i]) > 2) {
              // If '--d'
              if (argv[i][2] == 'd') {
                ivars.datafile = true;
              // If '--h'
              } else if (argv[i][2] == 'h') {
                display_help();
              // Invalid argument  
              } else {
                throw std::runtime_error(bad_arguments());
              }
            // Invalid argument  
            } else {
              throw std::runtime_error(bad_arguments());
            }
          // Invalid argument
          } else {
            throw std::runtime_error(bad_arguments());
          }
        }
      // Invalid argument
      } else {
        throw std::runtime_error(bad_arguments());
      }
    }
  }
}

// Local functions
std::string missing_arguments(){
  return "Invalid usage: Missing arguments\n"
         "Usage: ivex [-d data.iv] \".model\" | file.model iv.csv\n"
         "\n"
         "Please refer to the documentation for more info.";
}

std::string bad_arguments() {
  return "Invalid usage: Bad arguments.\n"
         "Please revise arguments. See usage.\n"
         "\n"
         "Usage: ivex [-d data.iv] \".model\" | file.model iv.csv\n"
         "\n"
         "Please refer to the documentation for more info.";
}

void display_help() {
  std::cout << "Usage: ivex [-d data.iv] \".model\" | file.model iv.csv\n"
               "\n"
               "data.iv is an optional space or comma seperated\n"
               "file containing current and voltage dat used for\n"
               "extracting a .model card\n"
               "\n"
               "\".model\" or file.model is a string/file where the model\n"
               "generated/sourced is saved/found\n"
               "\n"
               "iv.csv is the file where the simulated IV curve data is stored."
               << std::endl;
}
