//
// Created by nahomamit on 12/01/2020.
//

#include <fstream>
#include <iostream>
#include "CacheManager.h"
using namespace std;

class FileCacheManager: public CacheManager {
  virtual bool problemExist(string problem) {
    problem += ".txt";
    std::ifstream file(problem, ios::binary);
    if (file.is_open()) {
      file.close();
      return true;
    }
    return false;
  }

  virtual Solver getSolution(string problem) {
    Solver obj;
    problem += ".txt";
    std::ifstream file(problem, ios::binary);
    if (file.is_open()) {
      file.read((char *) &obj, sizeof(obj));
      file.close();
      return obj;
    }
  }
  virtual void addSolution(string problem, Solver solution) {
    problem += ".txt";
    ofstream file;
    file.open(problem, ios::binary);
    if (file.is_open()) {
      file.write((char *) &solution, sizeof(solution));
      file.close();
    }
  }

};