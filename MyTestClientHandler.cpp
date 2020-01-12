//
// Created by nahomamit on 12/01/2020.
//


#include <cstring>
#include "Solver.h"
#include "CacheManager.h"

using namespace std;
#include "ClientHandler.h"

class MyTestClientHandler: public ClientHandler {
  Solver solver;
  CacheManager cm;
 public:
  MyTestClientHandler(Solver solver1, CacheManager cache_manager) : solver(solver1), cm(cache_manager) {}
  void handleClient(string input, string output) {
    if (input == "end") {
      output = "end";
      return;
    } else {
      if (cm.problemExist(input)) {
        cm.getSolution(input);
      } else {
        Solver solution = solver.solve(input);
        cm.addSolution(input, solution);
      }
    }

  }
};