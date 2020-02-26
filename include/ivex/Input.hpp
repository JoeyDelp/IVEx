#include <JoSIM/Input.hpp>
#include <optional>
#include <string>

namespace ivex {
  struct ivex_vars {
    std::optional<std::string> 
      datafile_name, 
      modelfile_name, 
      model_string, 
      outputfile_name;
  };

  void input_parse(int argc, const char **argv, ivex_vars &ivars);
  
}