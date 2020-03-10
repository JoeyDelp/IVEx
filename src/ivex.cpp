#include <iostream>
#include <sstream>
#include "ivex/Input.hpp"
#include "ivex/Output.hpp"
#include "ivex/IV.hpp"
#include "ivex/Data.hpp"
#include "ivex/Extraction.hpp"

void version_info() {
  std::cout << "IVEx - JJ Current/Voltage Characteristics Extraction Tool" << std::endl;
  std::cout << "Copyright (C) 2020 by QCS (joeydelp@gmail.com)" << std::endl;
  std::cout << "v" << VERSION << "." << GIT_COMMIT_HASH << " compiled on " << __DATE__ << " at "
            << __TIME__ << std::endl;
  std::cout << std::endl;
}

int main(int argc, const char **argv) {
  version_info();
  std::streambuf* cout_buff = std::cout.rdbuf(); 
  std::stringstream buffer;
  try {
    ivex::ivex_vars ivars;
    // Read in sysargs and determine mode as model or data
    if (ivex::input_parse(argc, argv, ivars) != 1) exit(-1);
    JoSIM::Input input_object;
    ivex::iv_data iv_res;
    // If not a datafile
    if(!ivars.datafile_name) {
      // Generate IV curve
      ivex::parse_model(input_object, ivars);
      ivex::setup_transsim(input_object);
      std::cout.rdbuf(buffer.rdbuf());
      iv_res = ivex::calculate_iv_curve(ivars.current_limit, input_object);
      ivex::write_iv_curve(ivars, iv_res);
    } else {
      // Extract model
      ivex::iv_params params;
      ivex::iv_data iv_measured = ivex::read_data_file(ivars.datafile_name.value());
      ivex::iv_data iv_smoothed = ivex::smooth_noisy_data(iv_measured);
      params.crit_current = ivex::extract_critical_current(iv_smoothed, params.crit_index);
      params.volt_gap = ivex::extract_gap_voltage(iv_measured, params.crit_index, params.vgap_index);
      params.res_norm = ivex::extract_res_normal(iv_smoothed, params.vgap_index, params.normal_index);
      params.delta_v = ivex::extract_delta_v(iv_measured, params.vgap_index, params.normal_index);
      params.res_sub = ivex::extract_res_sub(iv_smoothed, params.crit_index, params.sub_index);
      params.ic_fact = ivex::extract_ic_fact(iv_smoothed, params.crit_current, params.normal_index, params.volt_gap);
      std::stringstream extracted_model;
      extracted_model << ".model jj_extract jj(icrit=" << params.crit_current << 
                         ", vgap=" << params.volt_gap << 
                         ", rn=" << params.res_norm << 
                         ", r0=" << params.res_sub << 
                         ", delv=" << params.delta_v << 
                         ", icfct=" << params.ic_fact << ")";
      std::cout.rdbuf(cout_buff);
      std::cout << extracted_model.str() << std::endl;
      ivars.model_string = extracted_model.str();
      ivex::parse_model(input_object, ivars);
      ivex::setup_transsim(input_object);
      std::cout.rdbuf(buffer.rdbuf());
      iv_res = ivex::calculate_iv_curve(ivars.current_limit, input_object);
      ivex::write_iv_curve(ivars, iv_res);
    }

  } catch (std::runtime_error &e) {
    std::cout.rdbuf(cout_buff);
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  exit(0);
}