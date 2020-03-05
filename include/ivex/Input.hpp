#ifndef IVEX_INPUT_HPP
#define IVEX_INPUT_HPP
#include <JoSIM/Input.hpp>
#include <JoSIM/Errors.hpp>
#include <optional>
#include <string>

namespace ivex {
  struct ivex_vars {
    std::optional<std::string> 
      datafile_name, 
      modelfile_name, 
      model_string, 
      outputfile_name;
    double current_limit{5E-4};
  };

  int input_parse(int argc, const char **argv, ivex_vars &ivars);

  void parse_model(JoSIM::Input &input_object, ivex_vars &ivars);

  void create_standard_netlist(JoSIM::Input &input_object, const std::string &cur_start_val, const std::string &cur_stop_val);

  void setup_transsim(JoSIM::Input &input_object);
  
}

#endif