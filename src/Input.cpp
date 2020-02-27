#include "ivex/Input.hpp"
#include <iostream>
#include <fstream>
#include "CLI/CLI.hpp"

using namespace ivex;

// Local function prototypes
std::string missing_arguments();
std::string bad_arguments();
void display_help();

class MyFormatter : public CLI::Formatter {
  public:
    MyFormatter() : Formatter() {}
    std::string make_option_opts(const CLI::Option *) const override { return ""; }
};

int ivex::input_parse(int argc, const char **argv, ivex_vars &ivars){
  CLI::App app;

  app.formatter(std::make_shared<MyFormatter>());

  CLI::Option* data_option = app.add_option("-d,--data", ivars.datafile_name, "File containing space/comma seperated IV data")
    ->check(CLI::ExistingFile);

  CLI::Option* model_option = app.add_option("-m,--model", ivars.modelfile_name, "File used for input/output of .model card");

  CLI::Option* string_option = app.add_option("-s,--smodel", ivars.model_string, "String representation of .model card to use");
  
  model_option->excludes(string_option);
  string_option->excludes(model_option);
  model_option->required();
  string_option->required();

  CLI::Option* output_positional = app.add_option("-o,--output,output.csv", ivars.outputfile_name, "Output comma seperated value (csv) used to store simulated IV data")
    ->required();

  CLI11_PARSE(app, argc, argv);
  return 0;
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
