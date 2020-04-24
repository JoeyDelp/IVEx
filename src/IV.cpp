#include "ivex/IV.hpp"
#include "ivex/Input.hpp"
#include <JoSIM/Matrix.hpp>
#include <JoSIM/Simulation.hpp>
#include <ios>
#include <numeric>
#include <iostream>
#include <sstream>
#include <omp.h>

double avg_voltage(std::vector<double> const& v) {
    return std::accumulate(v.begin() + (3*(v.size()/4)), v.end(), 0.0) / (static_cast<double>(v.size())/4);
}

std::string scietific_notation(const double &value) {
  std::ostringstream streamObj;
  streamObj << std::uppercase << value;
  return streamObj.str();  
}

ivex::iv_data ivex::calculate_iv_curve(const double &limit, JoSIM::Input &input_object) {
  int steps = round(limit/5E-7);
  ivex::iv_data iv_res;
  iv_res.resize(steps * 4, std::pair<double, double>());
  std::vector<JoSIM::Input> iobjs;
  iobjs.resize(steps * 4, input_object);
  std::vector<JoSIM::Matrix> mobjs;
  mobjs.resize(steps * 4, JoSIM::Matrix());
  std::vector<double> cstart, cstop;
  cstart.resize(steps * 4, double());
  cstop.resize(steps * 4, double());
#pragma omp parallel for ordered
  for (int i = 0; i < steps * 4; ++i) {
    double current_start, current_stop;
    if (i == 0) {
      cstart[i] = 0.0;
      cstop[i] = 0;
    } else if (i > 0 && i < steps) {
      cstart[i] = 0.0;
      cstop[i] = i * 5E-7;
    } else if (i == steps) {
      cstop[i] = cstart[i] = steps * 5E-7;
    } else if (i > steps && i < steps * 3) {
      cstart[i] = steps * 5E-7;
      cstop[i] = cstart[i] - ((i - steps) * 5E-7);
    } else if(i == 3 * steps) {
      cstop[i] = cstart[i] = -(steps * 5E-7);
    } else if (i > steps * 3 && i < steps * 4) { 
      cstart[i] = -(steps * 5E-7);
      cstop[i] = cstart[i] + ((i - (3 * steps)) * 5E-7);
    } 
  }
#pragma omp barrier
  for (int i = 0; i < steps * 4; ++i) {
    ivex::create_standard_netlist(iobjs.at(i), scietific_notation(cstart.at(i)), scietific_notation(cstop.at(i)));
    mobjs.at(i).create_matrix(iobjs.at(i));
  }
#pragma omp parallel for shared(iobjs, mobjs, cstop, iv_res)
  for (int i = 0; i < steps * 4; ++i) {
    JoSIM::Simulation simulation_object(iobjs.at(i), mobjs.at(i));
    iv_res.at(i) = std::make_pair(avg_voltage(simulation_object.results.xVector.at(0).value()), cstop.at(i));
  }
#pragma omp barrier
  return std::move(iv_res);
}