#include "ivex/Extraction.hpp"

double ivex::extract_critical_current(const ivex::iv_data &iv_measured) {
  double sum = 0, average = 0;
  for (int i = 0; i < iv_measured.size(); ++i) {
    sum += iv_measured.at(i).first;
    average = sum / i;
  }
}