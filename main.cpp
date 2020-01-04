#include <iostream>
#include <map>
#include "list"
#include "lexer.h"
#include "command.h"

extern bool flagServer;
extern bool flagClient;
std::map<std::string,command*> createCommandsMap();
void createServer( std::list<std::string> lexer);
void createClient(std::list<std::string> lexer);
std::map<std::string, command*> commandsMap;
int ifCommandPros(int x,std::list<std::string> lexer);
int whileCommandPros(std::list<std::string> lexer);

int main(int argc, char **argv) {
  std::ignore = argc;
  int x = 2;
  std::list<std::string> lexer;

  commandsMap = createCommandsMap();
  std::string nameObj = argv[1];
  lexer = lexerStart(nameObj);
  std::thread threadServer(createServer, lexer);
  while(!flagServer) {

  }
  lexer.pop_front();
  lexer.pop_front();
  std::thread threadClient(createClient, lexer);
  while(!flagClient) {

  }
  lexer.pop_front();
  lexer.pop_front();
  lexer.pop_front();
  while (!lexer.empty()) {
    std::string name =   lexer.front();
    std::map<std::string, command*>::iterator iter = commandsMap.find(name);
    if (iter == commandsMap.end()){
      x = commandsMap["="]->execute(lexer);
      lexer.pop_front();
    } else {
      lexer.pop_front();
      x = commandsMap[name]->execute(lexer);
      if(x<0){
        if(x == -4){
          x = whileCommandPros(lexer);
        } else {
          x = ifCommandPros(x, lexer);
        }
      }
    }
    for (int i = 0; i < x; i++) {
      lexer.pop_front();
    }
  }
  flagServer = false;
  threadClient.join();
  threadServer.join();
  return 0;
}
int whileCommandPros(std::list<std::string> lexer) {
  //int brackets = 1;
  int pops = 0;
  int x;
  int check;
  std::list<std::string> comList;
  std::list<std::string> checkLexer = lexer;
  //int y;
  while ((signed)lexer.front().find("{") == -1) {
    lexer.pop_front();
    pops++;
  }
  lexer.pop_front();
  pops++;
  while ((signed)lexer.front().find("}") == -1) {
    if (lexer.front() != "") {
      comList.push_back(lexer.front());
    }
    pops++;
    lexer.pop_front();
  }
  lexer.pop_front();
  pops++;
  check = commandsMap["if"]->execute(checkLexer);
  while ((signed)check == -2) {
    for (int i = 0; (unsigned)i < comList.size(); i++) {
      std::string nameObj = comList.front();
      comList.push_back(comList.front());
      comList.pop_front();
      std::map<std::string, command *>::iterator iter = commandsMap.find(nameObj);
      if (iter == commandsMap.end()) {
        comList.push_front(nameObj);
        x = commandsMap["="]->execute(comList);
        comList.pop_front();
      } else {
        x = commandsMap[nameObj]->execute(comList);
      }
      if (x < 0) {
        if (x == -4) {
          x = whileCommandPros(lexer);
        } else {
          x = ifCommandPros(x, lexer);
        }
      }
      for (int j = 0; j < x; j++) {
        comList.push_back(comList.front());
        comList.pop_front();
      }
    }
    check = commandsMap["if"]->execute(checkLexer);
  }
  return pops;
}

int ifCommandPros(int x, std::list<std::string> lexer) {
  int counter = 0;
  int tmp;
  int brackets = 0;
  while(lexer.front() != "{"){
    lexer.pop_front();
    counter++;
  }
  counter++;
  lexer.pop_front();
  if (x == -2) {
    while (lexer.front() != "}" && brackets != 1) {
      if (lexer.front() == "{") {
        brackets++;
        counter++;
        lexer.pop_front();
        continue;
      }
      if (lexer.front() == "}") {
        brackets--;
        counter++;
        lexer.pop_front();
        continue;
      }
      string nameObj = lexer.front();
      std::map<std::string, command*>::iterator iter = commandsMap.find(nameObj);
      lexer.pop_front();
      if (iter == commandsMap.end()) {
        tmp = commandsMap["="]->execute(lexer);
        lexer.pop_front();
      } else {
        lexer.pop_front();
        tmp = commandsMap[nameObj]->execute(lexer);
      }
      if (tmp < 0) {
        if (tmp == -4) {
          tmp = whileCommandPros(lexer);
        } else {
          tmp = ifCommandPros(tmp, lexer);
        }
      }
      counter += tmp + 1;
      for (int i = 0; i < tmp; i++) {
        lexer.pop_front();
      }

    }
  } else {
    while (lexer.front() != "}" && brackets != 1) {
      if (lexer.front() == "{") {
        counter++;
        brackets++;
        lexer.pop_front();
        continue;
      }
      if (lexer.front() == "}") {
        counter++;
        brackets--;
        lexer.pop_front();
        continue;
      }
      string nameObj = lexer.front();
      std::map<std::string, command *>::iterator iter = commandsMap.find(nameObj);
      if (iter == commandsMap.end()) {
        tmp = commandsMap["="]->execute(lexer);
        lexer.pop_front();
      } else {
        lexer.pop_front();
        tmp = commandsMap[nameObj]->execute(lexer);
      }
      if (tmp < 0) {
        if (tmp == -4) {
          tmp = whileCommandPros(lexer);
        } else {
          tmp = ifCommandPros(tmp, lexer);
        }
      }
      counter += tmp + 1;
      for (int i = 0; i < tmp; i++) {
        lexer.pop_front();
      }
    }
    return counter +1;
  }
  return 0; //check !!!!!!!!!!!!!!!!!!!!
}




std::map<std::string,command*> createCommandsMap(){
  std::map<std::string, command*> mapC;
  command *c = new openServerCommand();
  mapC["openDataServer"] = c;
  c = new connectCommand();
  mapC["connectControlClient"] = c;
  c = new defineVarCommand();
  mapC["var"] = c;
  c = new printCommend();
  mapC["Print"] = c;
  c = new sleepCommend();
  mapC["Sleep"] = c;
  c = new updateCommend();
  mapC["="] = c;
  c = new ifCommand();
  mapC["if"] = c;
  c = new whileCommand();
  mapC["while"] = c;
  return mapC;
}


void createServer( std::list<std::string> lexer) {
  commandsMap["openDataServer"]->execute(lexer);

}

void createClient(std::list<std::string> lexer) {
  commandsMap["connectControlClient"]->execute(lexer);
}