#include "ivex/Extraction.hpp"
#include <iostream>

double ivex::extract_critical_current(const ivex::iv_data &iv_smoothed, int &crit_index) {
  double grad = 0, prev_grad = 0, avg_grad = 0;
  prev_grad = abs(iv_smoothed.at(1).first - iv_smoothed.at(0).first)
              / abs(iv_smoothed.at(1).second - iv_smoothed.at(0).second);
  for (int i = 2; i < iv_smoothed.size() - 1; ++i) {
    grad = abs(iv_smoothed.at(i).first - iv_smoothed.at(i-1).first)
          / abs(iv_smoothed.at(i).second - iv_smoothed.at(i-1).second);
    avg_grad = (grad - prev_grad) / 2;
    if(avg_grad > 1) { 
      crit_index = i;
      return iv_smoothed.at(i).second;
    }
    prev_grad = grad;
  }
  return avg_grad;
}

double ivex::extract_gap_voltage(const ivex::iv_data &iv_measured, const int &crit_index, int &vgap_index) {
  double suspect_vgap = 0, next_vgap = 0;
  for (int i = crit_index + 1; i < iv_measured.size(); ++i) {
    suspect_vgap = iv_measured.at(i).first;
    next_vgap = iv_measured.at(i + 1).first;
    if((next_vgap - suspect_vgap) / next_vgap < 0.05) {
      vgap_index = i;
      return suspect_vgap;
    }
  }
  return suspect_vgap;
}

double ivex::extract_res_normal(const ivex::iv_data &iv_smoothed, const int &vgap_index, int &normal_index) {
  int peak_index = std::max_element(iv_smoothed.begin(),iv_smoothed.end()) - iv_smoothed.begin();
  double grad = 0, prev_grad = 0, avg_grad = 0;
  prev_grad = abs(iv_smoothed.at(vgap_index+1).first - iv_smoothed.at(vgap_index).first)
              / abs(iv_smoothed.at(vgap_index+1).second - iv_smoothed.at(vgap_index).second);
  for (int i = vgap_index + 2; i < peak_index - 1; ++i) {
    grad = abs(iv_smoothed.at(i).first - iv_smoothed.at(i-1).first)
          / abs(iv_smoothed.at(i).second - iv_smoothed.at(i-1).second);
    avg_grad = (grad - prev_grad) / 2;
    if(avg_grad > 1) { 
      normal_index = i;
      break;
    }
    prev_grad = grad;
  }
  double avg_v = 0, avg_c = 0;
  for (int i = normal_index; i < peak_index - 1; ++i) {
    avg_v += iv_smoothed.at(i).first;
    avg_c += iv_smoothed.at(i).second;
  }
  avg_v = avg_v / (peak_index - normal_index);
  avg_c = avg_c / (peak_index - normal_index);
  return avg_v / avg_c;
}

double ivex::extract_delta_v(const ivex::iv_data &iv_measured, const int &vgap_index, const int &normal_index) {
  return iv_measured.at(normal_index).first - iv_measured.at(vgap_index).first;
}

double ivex::extract_res_sub(const ivex::iv_data &iv_smoothed, const int &crit_index, int &sub_index) {
  int peak_index = std::max_element(iv_smoothed.begin(),iv_smoothed.end()) - iv_smoothed.begin();
  int crit_return_index = peak_index + (peak_index - crit_index);
  double grad = 0, prev_grad = 0, avg_grad = 0;
  prev_grad = abs(iv_smoothed.at(crit_return_index+1).first - iv_smoothed.at(crit_return_index).first)
              / abs(iv_smoothed.at(crit_return_index+1).second - iv_smoothed.at(crit_return_index).second);
  for (int i = crit_return_index + 2; i < iv_smoothed.size() - 1; ++i) {
    grad = abs(iv_smoothed.at(i).first - iv_smoothed.at(i-1).first)
          / abs(iv_smoothed.at(i).second - iv_smoothed.at(i-1).second);
    avg_grad = (grad - prev_grad) / 2;
    if(avg_grad > 1) { 
      sub_index = i;
      break;
    }
    prev_grad = grad;
  }
  int zero_point;
  if (iv_smoothed.size() > peak_index) {
    zero_point = 2 * peak_index;
  } else {
    zero_point = iv_smoothed.size();
  }
  double avg_v = 0, avg_c = 0;
  for (int i = sub_index; i < zero_point - 1; ++i) {
    avg_v += iv_smoothed.at(i).first;
    avg_c += iv_smoothed.at(i).second;
  }
  avg_v = avg_v / (zero_point - sub_index);
  avg_c = avg_c / (zero_point - sub_index);
  return avg_v / avg_c;
}

double ivex::extract_ic_fact(const ivex::iv_data &iv_smoothed, const double &crit_current, const int &normal_index, const double &voltage_gap) {
  int peak_index = std::max_element(iv_smoothed.begin(),iv_smoothed.end()) - iv_smoothed.begin();
  double x1 = iv_smoothed.at(normal_index + (peak_index - normal_index)/4).first;
  double x2 = iv_smoothed.at(normal_index + (peak_index - normal_index)/2).first;
  double y1 = iv_smoothed.at(normal_index + (peak_index - normal_index)/4).second;
  double y2 = iv_smoothed.at(normal_index + (peak_index - normal_index)/2).second;
  double gradient = (y2 - y1) / (x2 - x1);
  // y - y1 = m(x - x1)
  double y_intersection = gradient * (-x1) + y1;
  return crit_current / (gradient * voltage_gap + y_intersection);
}