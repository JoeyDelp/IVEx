#ifndef IVEX_DATA_HPP
#define IVEX_DATA_HPP

#include "./IV.hpp"

namespace ivex {

  ivex::iv_data read_data_file(const std::string &datafile_name);

  ivex::iv_data smooth_noisy_data(const ivex::iv_data &iv_measured);

}

#endif