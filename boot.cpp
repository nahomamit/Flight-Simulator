//
// Created by nahomamit on 12/01/2020.
//
#include "server.h"
#include "MySerialServer.cpp"
using namespace std;

class Main {
 public:
  int main(int argc, char **argv) {
    Server server = new MySerialServer();
    Solver solver = new stringReverser();
    CacheManager cache_manager = new FileCacheManager();
    ClientHandler client_handler = new MyTestClientHandler(solver, cache_manager);
    std::thread threadServer(openServer,server, argv[0], client_handler);



    threadServer.join();
    return 0;
  }

  void openServer(Server server, int port, ClientHandler client_handler) {
    server.open(port, client_handler);
  }
};