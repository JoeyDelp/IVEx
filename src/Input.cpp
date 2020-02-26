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
            try {
              ivars.datafile_name = argv[i+1];
            } catch (std::out_of_range &e) {
              throw std::runtime_error(missing_arguments());
            }
          // If '-h'
          } else if (argv[i][1] == 'h') {
            display_help();
            return;
          // If '--'
          } else if (argv[i][1] == '-') {
            if(sizeof(argv[i]) > 2) {
              // If '--d'
              if (argv[i][2] == 'd') {
                try {
                  ivars.datafile_name = argv[i+1];
                } catch (std::out_of_range &e) {
                  throw std::runtime_error(missing_arguments());
                }
              // If '--h'
              } else if (argv[i][2] == 'h') {
                display_help();
                return;
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
        // Test rest of arguments
        } else {
          //If model has not been set
          if (!ivars.model_string && !ivars.modelfile_name) {
            // If string
            if(argv[i][0] == '\"') {
              try{
                if(argv[i][sizeof(argv[i])-1] == '\"') {
                  ivars.model_string = argv[i];
                } else {
                  throw std::runtime_error(bad_arguments());
                }
                // ivars.model_string = argv[i + 1];
                // int j = i + 2;
                // while(argv[j][sizeof(argv[j])-1] != '\"') {
                //   ivars.model_string = ivars.model_string.value() + " " + argv[j];
                // }
                // i = j;
              } catch (std::out_of_range &e) {
                throw std::runtime_error(bad_arguments());
              }
            // Its a file
            } else {
              ivars.modelfile_name = argv[i];
            }
          // Argument is output file name
          } else {
            ivars.outputfile_name = argv[i];
          }
        }
      // Invalid argument
      } else {
        throw std::runtime_error(bad_arguments());
      }
    }
  }
  if(!(ivars.model_string || ivars.modelfile_name) || !ivars.outputfile_name) {
    throw std::runtime_error(bad_arguments());
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
