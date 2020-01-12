//
// Created by nahomamit on 12/01/2020.
//

#ifndef FLIGHTSIMULATORGAL__SOLVER_H_
#define FLIGHTSIMULATORGAL__SOLVER_H_
#include <string>
using namespace std;


class Solver {
 public:
  virtual Solver solve(string problem);
};

#endif //FLIGHTSIMULATORGAL__SOLVER_H_
