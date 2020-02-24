#include "ivex/Input.hpp"
#include <fstream>
#include <optional>

using namespace ivex;

void ivex::input_parse(int argc, const char **argv){
  if (argc <= 1) {
    throw std::runtime_error("Invalid usage: Missing input arguments\n"
                             "Usage: ivex [-d data.iv] \".model\" | file.model\n"
                             "\n"
                             "Please refer to the documentation for more info.");
  } else {
    for (int i = 1; i < argc; ++i) {
      if(sizeof(argv[i]) > 1) {
        if (argv[i][0] == '-') {
          if (argv[i][1] == 'd') {
            ivars.datafile = true;
          } else if (argv[i][1] == 'h') {
            throw std::runtime_error("Usage: ivex [-d data.iv] \".model\" | file.model\n");
          } else {
            throw std::runtime_error("Invalid usage: Bad arguments.\n"
                                 "Please revise arguments. See usage.");
          }
        }
      } else {
        throw std::runtime_error("Invalid usage: Bad arguments.\n"
                                 "Please revise arguments. See usage.");
      }
    }
  }
}