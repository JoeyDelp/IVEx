#include "ivex/Output.hpp"

void ivex::write_iv_curve(const ivex::ivex_vars &ivars, const ivex::iv_data &iv_result, std::optional<ivex::iv_data> iv_measured) {
  std::ofstream outfile(ivars.outputfile_name.value());
  if (outfile.is_open()) {
    if (iv_measured) {
      int loopsize = (iv_result.size() > iv_measured.value().size()) ? iv_measured.value().size() : iv_result.size(); 
      for(int i = 0; i < loopsize; ++i) {
        outfile << iv_measured.value().at(i).first << ", " <<
                   iv_measured.value().at(i).second << ", " <<
                   iv_result.at(i).first << ", " <<
                   iv_result.at(i).second << std::endl;
      }  
    } else {
      for (auto i : iv_result) {
        outfile << i.first << "," << i.second << std::endl;
      }
    }
    outfile.close();
  }
}

void ivex::write_model_to_file(const ivex::ivex_vars &ivars, const std::string &model_string) {
  std::ofstream outfile(ivars.modelfile_name.value(), std::ios_base::app);
  if (outfile.is_open()) {
    outfile << model_string << std::endl;
    outfile.close();
  }
}