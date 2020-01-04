//
// Created by nahomamit on 23/12/2019.
//

#include <fstream>
#include <algorithm>
#ifndef FLIGHTSIMULATORGAL__LEXER_H_
#define FLIGHTSIMULATORGAL__LEXER_H_

#endif //FLIGHTSIMULATORGAL__LEXER_H_


std::list<std::string> splitsBySpace(std::ifstream & file);
std::list<std::string> splitsByBrackets(std::string source);
std::list<std::string> splitsByChar(std::string source, char ch);

std::list<std::string> lexerStart(std::string fileName) {
  std::ifstream file (fileName, std::ifstream::in);
  if (!file.is_open()) {
    std::cout<< "file doesnt opened !" <<std::endl;
    throw "file doesnt opened !";
  }
  return splitsBySpace(file);
}

std::list<std::string> splitsBySpace(std::ifstream & file) {
  std::list<std::string> splits;
  std::list<std::string> tempSplits;
  std::string line;
  while (getline(file,line)) {
    while(line[0] == ' '){
      line = line.substr(1, line.length()-1);
    }
    std::remove( line.begin(), line.end(), '\t');
    int flag = line.find(" = ");
    if (flag != -1) {
      if((signed)line.find("var") == -1) {
        splits.push_back(line.substr(0, flag));
        splits.push_back("=");
        splits.push_back(line.substr(flag + 3));
        continue;
      }else {
        splits.push_back("var");
        line = line.substr(4);
        flag = line.find(" = ");
        splits.push_back(line.substr(0,flag));
        splits.push_back("=");
        splits.push_back(line.substr(flag + 3));
        continue;
      }
    }
    int index = 0;
    while ((unsigned)index < line.length()) {
      int space = line.substr(index).find(' ');
      if (space == -1) {
        tempSplits = splitsByBrackets(line.substr(index));
        for (std::string str : tempSplits) {
          if (str != ")") {
            splits.push_back(str);
          }
        }
        break;
      } else {
        tempSplits = splitsByBrackets(line.substr(index));
        for (std::string str : tempSplits) {
          if (str != ")") {
            splits.push_back(str);
          }
          index = line.find(str) + str.length();
        }
        index++;
      }
    }
  }

  return splits;
}

std::list<std::string> splitsByBrackets(std::string word) {
  std::list<std::string> splits;
  std::list<std::string> splitsComma;
  int openBracket = word.find('(');
  if (openBracket != -1) {
    int closeBracket = word.find(')');
    splits = splitsByChar(word.substr(0, openBracket), ' ');
    splitsComma = splitsByChar(word.substr(openBracket + 1, closeBracket - openBracket - 1), ',');
    for (std::string str : splitsComma) {
      if((signed)str.find(('"')) != -1) {
        str = str.substr(1, str.length() - 2);
      }
      splits.push_back(str);
    }

  } else {
    splits = splitsByChar(word, ' ');
  }
  return splits;
}



std::list<std::string> splitsByChar(std::string source, char ch) {

  std::list<std::string> splits;
  std::string temp;
  int wordIndex = 0;
  int commaIndex = source.find(ch);
  while (commaIndex != -1) {
    splits.push_back(source.substr(wordIndex, commaIndex));
    wordIndex = wordIndex + commaIndex + 1;
    temp = source.substr(wordIndex);
    commaIndex = temp.find(ch);
  }
  if ((unsigned)wordIndex < source.length()) {
    if ((signed)source.substr(wordIndex).find(ch) != -1) {
      splits.push_back(source.substr(wordIndex + 1));
    } else {
      splits.push_back(source.substr(wordIndex));
    }
  }
  return splits;
}