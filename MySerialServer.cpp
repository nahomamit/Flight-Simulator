//
// Created by nahomamit on 12/01/2020.
//

using namespace std;
#include <bits/socket.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include "server.h"
#include <string.h>

class MySerialServer: public Server {
  virtual void open(int port, ClientHandler c) {
    bool flag = true;
    int clientSocket;

    char buffer[1024] = {0};

    while (true) {
      while (flag) {
        clientSocket = getClientInfo(port);
        read(clientSocket, buffer, 1024);
        if (strlen(buffer) != 0) {
          flag = false;
        }
      }
      flag = true;
    }
  }
  virtual void stop() {

  }

  int getClientInfo(int port) {
    std::string::size_type sz;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
      cerr << "Could not create a Socket" << endl;
      return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
      std::cerr << "could not bind the socket to an IP" << std::endl;
    }
    if (listen(socketfd, 5) == -1) {
      std::cerr << "error during listening" << std::endl;
      return -2;
    }
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    if ((client_socket) < 0) {
      std::cerr << "error accepting client" << std::endl;
      return -3;
    }
    return client_socket;
  }

  }
};
