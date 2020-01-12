//
// Created by nahomamit on 12/01/2020.
//

#include "Solver.h"
using namespace std;

class stringReverser: public Solver {
  string solution = "";
 public:
  virtual Solver solve(string problem) {
    for (int i = 0; i < problem.length() / 2; i++)
      swap(problem[i], problem[problem.length() - i - 1]);
    solution = problem;
    return *this;
  }

};