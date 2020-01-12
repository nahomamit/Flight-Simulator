//
// Created by nahomamit on 12/01/2020.
//

#ifndef FLIGHTSIMULATORGAL__CLIENTHANDLER_H_
#define FLIGHTSIMULATORGAL__CLIENTHANDLER_H_

#endif //FLIGHTSIMULATORGAL__CLIENTHANDLER_H_
#include <unistd.h>
#include <string>
#include "Solver.h"
#include "CacheManager.h"
using namespace std;
class ClientHandler {
 public:
  virtual void handleClient(string input, string output);
  virtual ~ClientHandler(){};
};