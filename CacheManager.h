//
// Created by nahomamit on 12/01/2020.
//

#ifndef FLIGHTSIMULATORGAL__CACHEMANAGER_H_
#define FLIGHTSIMULATORGAL__CACHEMANAGER_H_

#include <string>
#include "Solver.h"
using namespace std;

class CacheManager {
 public:

  virtual bool problemExist(string problem);
  virtual Solver getSolution(string problem);
  virtual void addSolution(string problem, Solver solution);
};

#endif //FLIGHTSIMULATORGAL__CACHEMANAGER_H_
