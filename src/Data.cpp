#include "ivex/Data.hpp"
#include <fstream>
#include <regex>

ivex::iv_data ivex::read_data_file(const std::string &datafile_name) {
  ivex::iv_data iv_measured;
  std::ifstream file(datafile_name);
  std::string line;
  size_t delpos;
  while (std::getline(file, line)) {
    line = std::regex_replace(line, std::regex("^ +| +$|( ) +"), "$1");
    delpos = line.find_first_of(", \t");
    if(
      line.substr(delpos + 1, line.size()).substr(
        line.substr(delpos + 1, line.size()).find_first_not_of(", \t"),
        line.substr(delpos + 1, line.size()).size()
      ).find_first_of(", \t") != std::string::npos
    ) {
      throw std::runtime_error("E: Data Input\n"
                               "The file specified does not conform to the correct format.\n"
                               "Only files containing values of voltage (delimeter) current\n"
                               "are allowed. Additional junk in the file produces this error.\n\n"
                               "Infringing line: " + line + "\n\n"
                               "Please check the specified file and try again.");
    }
    iv_measured.emplace_back(
      std::make_pair(
        std::stod(line.substr(0, delpos)), 
        std::stod(line.substr(delpos + 1, line.size()))
      )
    );
  }
  return iv_measured;
}

ivex::iv_data ivex::smooth_noisy_data(const ivex::iv_data &iv_measured) {
  ivex::iv_data iv_smoothed;
  double avg_v = 0;
  for(int i = 0; i < iv_measured.size(); ++i) {
    if(i == 0) {
      avg_v = (3*iv_measured.at(i).first + 2*iv_measured.at(i+1).first + iv_measured.at(i+2).first) / 6;
    } else if (i == 1) {
      avg_v = (2*iv_measured.at(i-1).first + 3*iv_measured.at(i).first + 2*iv_measured.at(i+1).first + iv_measured.at(i+2).first) / 8;
    } else if (i == iv_measured.size() - 2) {
      avg_v = (iv_measured.at(i-2).first + 2*iv_measured.at(i-1).first + 3*iv_measured.at(i).first + 2*iv_measured.at(i+1).first) / 8;
    } else if (i == iv_measured.size() - 1) {
      avg_v = (iv_measured.at(i-2).first + 2*iv_measured.at(i-1).first + 3*iv_measured.at(i).first) / 6;
    } else {
      avg_v = (iv_measured.at(i-2).first + 2*iv_measured.at(i-1).first + 3*iv_measured.at(i).first + 2*iv_measured.at(i+1).first + iv_measured.at(i).first) / 9;
    }
    iv_smoothed.emplace_back(std::make_pair(avg_v, iv_measured.at(i).second));
  }
  return iv_smoothed;
}