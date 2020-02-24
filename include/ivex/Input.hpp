#include <JoSIM/Input.hpp>
#include <optional>
#include <string>

namespace ivex {
  struct ivex_vars {
    ivex_vars() : datafile(false) {}
    std::optional<std::string> datafile_name, modelfile_name, input_string;
    bool datafile;
  } ivars;

  void input_parse(int argc, const char **argv);
  
}