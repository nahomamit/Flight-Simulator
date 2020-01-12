//
// Created by nahomamit on 12/01/2020.
//

#ifndef FLIGHTSIMULATORGAL__SEVER_H_
#define FLIGHTSIMULATORGAL__SEVER_H_

#endif //FLIGHTSIMULATORGAL__SEVER_H_
#include <unistd.h>
#include "ClientHandler.h"

using namespace std;
class Server {
 public:
  virtual void open(int port, ClientHandler c);
  virtual void stop();
  virtual ~Server() {};
};


