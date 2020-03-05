#include "ivex/Input.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CLI/CLI.hpp"

using namespace ivex;

class MyFormatter : public CLI::Formatter {
  public:
    MyFormatter() : Formatter() {}
    std::string make_option_opts(const CLI::Option *) const override { return ""; }
};

int ivex::input_parse(int argc, const char **argv, ivex_vars &ivars){
  CLI::App app;
  app.formatter(std::make_shared<MyFormatter>());
  auto string_or_file = app.add_option_group("Model string or model file","");


  CLI::Option* data_file = app.add_option("-d,--data", ivars.datafile_name, "File containing space/comma seperated IV data")
    ->check(CLI::ExistingFile);

  CLI::Option* model_file = string_or_file
    ->add_option("-m,--model", ivars.modelfile_name, "File used for input/output of .model card");

  CLI::Option* model_string = string_or_file
      ->add_option("-s,--smodel", ivars.model_string, "String representation of .model card to use");

  string_or_file->require_option(1);

  app.add_option("-l,--limit", ivars.current_limit, "Limit the current to which the IV curve will sweep", true);

  app.add_option("output.csv", ivars.outputfile_name, "Output comma seperated value (csv) used to store simulated IV data")
    ->required();

  if(!ivars.datafile_name) model_file->check(CLI::ExistingFile);

  try { 
    app.parse((argc), (argv)); 
  } catch(const CLI::ParseError &e) { 
    return app.exit(e); 
  }
  return 1;
}

void ivex::parse_model(JoSIM::Input &input_object, ivex_vars &ivars) {
  if(ivars.modelfile_name) {
    std::string line;
    std::ifstream ifile(ivars.modelfile_name.value());
    std::vector<std::string> fileLines;
    if (ifile.is_open()) {
      while (!ifile.eof()) {
        getline(ifile, line);
        if(!line.empty()) {
          std::transform(line.begin(), line.end(), line.begin(), ::toupper);
          fileLines.emplace_back(line);
        }
      }
      if (fileLines.empty()) { 
        JoSIM::Errors::input_errors(JoSIM::InputErrors::EMPTY_FILE, ivars.modelfile_name.value());
      }
    } else {
      JoSIM::Errors::input_errors(JoSIM::InputErrors::CANNOT_OPEN_FILE, ivars.modelfile_name.value());
    }
    ivars.model_string = fileLines.back();
  } else {
    if(ivars.model_string.value().front() == '\"') ivars.model_string = ivars.model_string.value().substr(1);
    if(ivars.model_string.value().back() == '\"') ivars.model_string = ivars.model_string.value().substr(0, ivars.model_string.value().size() - 1);
    std::transform(ivars.model_string.value().begin(), ivars.model_string.value().end(), ivars.model_string.value().begin(), ::toupper);
  }
  JoSIM::Model::parse_model(std::make_pair(ivars.model_string.value(), std::string("")), input_object.netlist.models_new, input_object.parameters);
}

void ivex::create_standard_netlist(JoSIM::Input &input_object, const std::string &cur_start_val, const std::string &cur_stop_val) {
  if(input_object.netlist.models_new.size() != 0) {
    input_object.netlist.maindesign.emplace_back("IS 0 1 PWL(0 0 10P " + cur_start_val + " 50P " + cur_stop_val + ")");
    input_object.netlist.maindesign.emplace_back("B1 1 0 " + input_object.netlist.models_new.at(0).first.get_modelName() + " AREA=1");
    input_object.netlist.expand_maindesign();
  } else {
    throw(std::runtime_error("Missing model.\n Please ensure that a model was specified."));
  }
}

void ivex::setup_transsim(JoSIM::Input &input_object) {
  input_object.transSim.set_tstop(1E-9);
  input_object.transSim.set_prstep(5E-14);
  input_object.transSim.set_simsize();
}
