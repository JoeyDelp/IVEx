#ifndef IVEX_EXTRACTION_HPP
#define IVEX_EXTRACTION_HPP

#include "./IV.hpp"

namespace ivex {

  struct iv_params {
    double crit_current;
    double volt_gap;
    double res_norm;
    double res_sub;
    double ic_fact;
    double delta_v;
    int crit_index;
    int vgap_index;
    int normal_index;
    int sub_index;
  };

  double extract_critical_current(const ivex::iv_data &iv_smoothed, int &crit_index);

  double extract_gap_voltage(const ivex::iv_data &iv_measured, const int &crit_index, int &vgap_index);

  double extract_res_normal(const ivex::iv_data &iv_smoothed, const int &vgap_index, int &normal_index);

  double extract_delta_v(const ivex::iv_data &iv_measured, const int &vgap_index, const int &normal_index);

  double extract_res_sub(const ivex::iv_data &iv_smoothed, const int &crit_index, int &sub_index);

  double extract_ic_fact(const ivex::iv_data &iv_measured, const double &crit_current, const int &vgap_index, const int &normal_index);
}

#endif