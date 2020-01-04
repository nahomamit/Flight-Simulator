//
// Created by nahomamit on 23/12/2019.
//

#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include "Expression.cpp"
#include "sstream"

#ifndef FLIGHTSIMULATORGAL__COMMAND_H_
#define FLIGHTSIMULATORGAL__COMMAND_H_

#endif //FLIGHTSIMULATORGAL__COMMAND_H_
int client_socket2;
bool flagServer = false;
bool flagClient = false;
class variable;
std::map<std::string, variable*> serverMap;
std::map<std::string, variable*> varDefinitionMap;
std::string varsArr[36];
pair<string,int> readUntilChar(std::list<std::string> lexer, string s);
string findNextOperator(string s);
std::string createVarList();
float expressionChecker(std::string value);
class variable{
 protected:
  float val;
  std::string simLocation;
  int direction = 0;
 public:
  variable(std::string loc, float v) {
    val = v;
    simLocation = loc;
  }
  variable(std::string loc, float v, int dire)
  {
    val = v;
    simLocation = loc;
    direction = dire;
  }
  void setValue(float x) {
    val = x;
  }
  std::string getLocation(){
    return simLocation;
  }
  float getValue(){
    return val;
  }
  int getDirection(){
    return direction;
  }
  void setDirection(int x){
    direction = x;
  }
};


void createMapOfXML(){

  varsArr[0] ="airspeed-indicator_indicated-speed-kt";
  serverMap["airspeed-indicator_indicated-speed-kt"]=new variable("/instrumentation/airspeed-indicator/indicated-speed-kt", 0);
  varsArr[1] ="time_warp";
  serverMap["time_warp"]=new variable("/sim/time/warp", 0);
  varsArr[2] ="switches_magnetos";
  serverMap["switches_magnetos"]=new variable("/controls/switches/magnetos",0);
  varsArr[3] ="heading-indicator_offset-deg";
  serverMap["heading-indicator_offset-deg"]=new variable("/instrumentation/heading-indicator/offset-deg",0);
  varsArr[4] ="altimeter_indicated-altitude-ft";
  serverMap["altimeter_indicated-altitude-ft"]=new variable("/instrumentation/altimeter/indicated-altitude-ft",0);
  varsArr[5] ="altimeter_pressure-alt-ft";
  serverMap["altimeter_pressure-alt-ft"]=new variable("/instrumentation/altimeter/pressure-alt-ft",0);
  varsArr[6] ="attitude-indicator_indicated-pitch-deg";
  serverMap["attitude-indicator_indicated-pitch-deg"]=new variable("/instrumentation/attitude-indicator/indicated-pitch-deg",0);
  varsArr[7] ="attitude-indicator_indicated-roll-deg";
  serverMap["attitude-indicator_indicated-roll-deg"]=new variable("/instrumentation/attitude-indicator/indicated-roll-deg",0);
  varsArr[8] ="attitude-indicator_internal-pitch-deg";
  serverMap["attitude-indicator_internal-pitch-deg"]=new variable("/instrumentation/attitude-indicator/internal-pitch-deg",0);
  varsArr[9] ="attitude-indicator_internal-roll-deg";
  serverMap["attitude-indicator_internal-roll-deg"]=new variable("/instrumentation/attitude-indicator/internal-roll-deg",0);
  varsArr[10] ="encoder_indicated-altitude-ft";
  serverMap["encoder_indicated-altitude-ft"]=new variable("/instrumentation/altimeter/indicated-altitude-ft",0);
  varsArr[11] ="encoder_pressure-alt-ft";
  serverMap["encoder_pressure-alt-ft"]=new variable("/instrumentation/altimeter/pressure-alt-ft",0);
  varsArr[12] ="gps_indicated-altitude-ft";
  serverMap["gps_indicated-altitude-ft"]=new variable("/instrumentation/gps/indicated-altitude-ft",0);
  varsArr[13] ="gps_indicated-ground-speed-kt";
  serverMap["gps_indicated-ground-speed-kt"]=new variable("/instrumentation/gps/indicated-ground-speed-kt",0);
  varsArr[14] ="gps_indicated-vertical-speed";
  serverMap["gps_indicated-vertical-speed"]=new variable("/instrumentation/gps/indicated-vertical-speed",0);
  varsArr[15] ="indicated-heading-deg";
  serverMap["indicated-heading-deg"]=new variable("/instrumentation/heading-indicator/indicated-heading-deg",0);
  varsArr[16] ="magnetic-compass_indicated-heading-deg";
  serverMap["magnetic-compass_indicated-heading-deg"]=new variable("/instrumentation/magnetic-compass/indicated-heading-deg",0);
  varsArr[17] ="slip-skid-ball_indicated-slip-skid";
  serverMap["slip-skid-ball_indicated-slip-skid"]=new variable("/instrumentation/slip-skid-ball/indicated-slip-skid",0);
  varsArr[18] ="turn-indicator_indicated-turn-rate";
  serverMap["turn-indicator_indicated-turn-rate"]=new variable("/instrumentation/turn-indicator/indicated-turn-rate",0);
  varsArr[19] ="vertical-speed-indicator_indicated-speed-fpm";
  serverMap["vertical-speed-indicator_indicated-speed-fpm"]=new variable("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0);
  varsArr[20] ="flight_aileron";
  serverMap["flight_aileron"]=new variable("/controls/flight/aileron",0);
  varsArr[21] ="flight_elevator";
  serverMap["flight_elevator"]=new variable("/controls/flight/elevator",0);
  varsArr[22] ="flight_rudder";
  serverMap["flight_rudder"]=new variable("/controls/flight/rudder",0);
  varsArr[23] ="flight_flaps";
  serverMap["flight_flaps"]=new variable("/controls/flight/flaps",0);
  varsArr[24] ="engine_throttle";
  serverMap["engine_throttle"]=new variable("/controls/engines/engine/throttle",0);
  varsArr[25] ="current-engine_throttle";
  serverMap["current-engine_throttle"]=new variable("/controls/engines/current-engine/throttle",0);
  varsArr[26] ="switches_master-avionics";
  serverMap["switches_master-avionics"]=new variable("/controls/switches/master-avionics",0);
  varsArr[27] ="switches_starter";
  serverMap["switches_starter"]=new variable("/controls/switches/starter",0);
  varsArr[28] ="active-engine_auto-start";
  serverMap["active-engine_auto-start"]=new variable("/engines/active-engine/auto-start",0);
  varsArr[29] ="flight_speedbrake";
  serverMap["flight_speedbrake"]=new variable("/controls/flight/speedbrake",0);
  varsArr[30] ="c172p_brake-parking";
  serverMap["c172p_brake-parking"]=new variable("/sim/model/c172p/brake-parking",0);
  varsArr[31] ="engine_primer";
  serverMap["engine_primer"]=new variable("/controls/engines/engine/primer",0);
  varsArr[32] ="current-engine_mixture";
  serverMap["current-engine_mixture"]=new variable("/controls/engines/current-engine/mixture",0);
  varsArr[33] ="switches_master-bat";
  serverMap["switches_master-bat"]=new variable("/controls/switches/master-bat",0);
  varsArr[34] = "switches_master-alt";
  serverMap["switches_master-alt"]=new variable("/controls/switches/master-alt",0);
  varsArr[35] = "engine_rpm";
  serverMap["engine_rpm"]=new variable("/engines/engine/rpm",0);
}
class command {
 public:
  virtual int execute(std::list<std::string> lexer) = 0;
  virtual ~ command() {};
};

class openServerCommand: public command {

 public:
  std::mutex mutex2;
  int execute(std::list<std::string> lexer) {

    int clientInfo = CreateServer(lexer);
    mutex2.unlock();
    getInfo(clientInfo);
    close(client_socket2);
    return 1;
  }

  int CreateServer(std::list<std::string> lexer){
    lexer.pop_front();
    createMapOfXML();
    std::string::size_type sz;
    int port = stod(lexer.front(), &sz);
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
      std::cerr<<"Could not create a Socket" << std::endl;
      return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if(bind(socketfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
      std::cerr<<"could not bind the socket to an IP"<< std::endl;
    }
    if(listen(socketfd,5) == -1){
      std::cerr<<"error during listening"<< std::endl;
      return -3;
    }
    int client_socket = accept(socketfd, (struct sockaddr *)&address,(socklen_t*)&address);
    if ((client_socket)<0)
    {
      std::cerr<<"error accepting client" << std::endl;
      return -4;
    }
    flagServer = true;
    return client_socket;

  }

  void getInfo(int clientSocket) {
    std::mutex mutex_lock;
    char buffer[1024] = {0};
    //int j = 0;
    int i = 0;
    while (flagServer) {
      mutex_lock.lock();
      read(clientSocket, buffer, 1024);
      std::string strBudder = buffer;
      std::list<std::string> bufferByComma = splitsByChar(strBudder.substr(0, strBudder.find("\n")), ',');
      for (std::string str : bufferByComma) {
        if (i == 36) {
          break;
        }
        std::string::size_type sz;
        if(str== ""){
          i++;
          continue;
        }
        float val = stod(str, &sz);
        std::string name = varsArr[i];
        serverMap[varsArr[i]]->setValue(val);
        i++;
      }

      try{
        for (auto itr = serverMap.begin(); itr != serverMap.end(); ++itr) {
          for (auto itr2 = varDefinitionMap.begin(); itr2 != varDefinitionMap.end(); ++itr2) {
            if ((itr->second->getLocation() == itr2->second->getLocation()) && itr2->second->getDirection() == -1) {
              std::string name = itr2->first;
              int dire = itr2->second->getDirection();
              //float t = itr->second->getValue();
              varDefinitionMap[name] = itr->second;
              varDefinitionMap[name]->setDirection(dire);
            }
          }
        }} catch (exception e){
        cout<<"get info"<<endl;
      }
      i = 0;
      mutex_lock.unlock();
    }
  }

};

class connectCommand: public command{
  int execute(std::list<std::string> lexer) {
    connectClient(lexer);
    return 2;
  }
  static int connectClient(std::list<std::string> lexer){
    //create socket
    client_socket2 = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket2 == -1) {
      //error
      std::cerr << "Could not create a socket"<<std::endl;
      return -1;
    }
    lexer.pop_front();
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    std::string addressTemp = lexer.front();
    address.sin_addr.s_addr = inet_addr(addressTemp.c_str());
    lexer.pop_front();
    std::string::size_type sz;
    int port = stod(lexer.front(), &sz);
    address.sin_port = htons(port);

    int is_connect = connect(client_socket2, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
      std::cerr << "Could not connect to host server"<<std::endl;
      return -2;
    }
    flagClient = true;
    return 2;
  }
};

class defineVarCommand : public command{
 public:
  int execute(std::list<std::string> lexer) {

    int direct = 0;
    std::string name = lexer.front();
    lexer.pop_front();
    if(lexer.front() == "->"){
      direct = 1;
      lexer.pop_front();
      lexer.pop_front();
      varDefinitionMap[name] = new variable(lexer.front(), 0, direct);
    } else if(lexer.front()=="<-"){
      direct = -1;
      lexer.pop_front();
      lexer.pop_front();
      std::string loc = lexer.front();
      int location = findFromLocation(loc);
      float value = serverMap[varsArr[location]]->getValue();
      varDefinitionMap[name] = new variable(lexer.front(),value , direct);
    }else{
      try {
        std::map<std::string, variable*>::iterator iter = varDefinitionMap.find(name);
        lexer.pop_front();
        float x = expressionChecker(lexer.front());
        if(iter == varDefinitionMap.end()){
          variable *v = new variable("local", x, 0);
          varDefinitionMap[name] = v;
        } else {
          varDefinitionMap[name]->setValue(x);;
        }
        return 3;
      } catch (std::exception e) {
        std::cout << "error expression" << std::endl;
      }
      return 3;
    }
    return 4;
  }
  int findFromLocation(std::string loc){
    for(int i = 0; i <= 35; i++){
      if(serverMap[varsArr[i]]->getLocation() == loc){
        return i;
      }
    }
    return -1;
  }
};

class printCommend : public command{
 public:
  int execute(std::list<std::string> lexer) {
    try{
      std::cout << expressionChecker(lexer.front())<< std::endl;
    }catch (const char* c){
      std::cout << lexer.front() << std::endl;
    }
    return 1;
  }
};

class sleepCommend : public command{
 public:
  int execute(std::list<std::string> lexer) {
    int time = stod(lexer.front());
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    return 1;

  }
};

class updateCommend : public command{
 public:
  int execute(std::list<std::string> lexer) {

    std::string varName = lexer.front();
    lexer.pop_front();
    lexer.pop_front();
    std::string varList = "";
    try {
      std::map<std::string, variable*>::iterator iter = varDefinitionMap.find(varName);
      if(iter == varDefinitionMap.end()){
        varDefinitionMap[varName] = new variable("local", 0,0);
      }
      float expCalc = expressionChecker(lexer.front());
      varDefinitionMap[varName]->setValue(expCalc);
    } catch (std::exception e) {
      std::cout << "error expression" << std::endl;
    }
    std::ostringstream strs;
    strs << varDefinitionMap[varName]->getValue();
    std::string str = strs.str();
    std::string updateTemp = "set " + varDefinitionMap[varName]->getLocation() + " " + str + "\r\n";
    const char* update = updateTemp.c_str();
    int is_sent = write(client_socket2 , update, updateTemp.length());
    if (is_sent == -1) {
      cout<<client_socket2<<endl;
      is_sent = write(client_socket2 , update, updateTemp.length());
    }
    return 2;
  }
};

class ifCommand : public command{
 public:
  int execute(std::list<std::string> lexer) {
    pair<string,int> lValPair =  readUntilChar(lexer, "@");
    std::string leftVal =lValPair.first;
    while(lValPair.second != 0){
      lexer.pop_front();
      lValPair.second--;
    }
    std::string operat = lexer.front();
    lexer.pop_front();
    pair<string,int> RValPair =  readUntilChar(lexer, "{");
    std::string rightVal = RValPair.first;
    lexer.pop_front();
    float l = expressionChecker(leftVal);
    float r= expressionChecker(rightVal);
    //std::map<std::string, variable*>::iterator iter = varDefinitionMap.find(leftVal);
    int trueI = -2;
    int falseI = -3;
    if(operat == "<="){
      if(l<=r)
        return trueI;
      else
        return falseI;
    }
    if(operat == ">="){
      if(l>=r)
        return trueI;
      else
        return falseI;
    }
    if(operat == "<"){
      if(l<r)
        return trueI;
      else
        return falseI;
    }
    if(operat == ">"){
      if(l>r)
        return trueI;
      else
        return falseI;
    }
    if(operat == "=="){
      if(l==r)
        return trueI;
      else
        return falseI;
    }
    return -1;
  }
};
class whileCommand : public command{
 public:
  int execute(std::list<std::string> lexer) {
    lexer.front();
    return -4;
  }
};

string removeSpaces(string s){
  string c="";
  for(int i = 0; (unsigned)i < s.length();i++){
    if(s[i] != ' '){
      c += s[i];
    }
  }
  return c;

}
std::string createVarList(){
  std::string varList = "";
  for(auto itr = varDefinitionMap.begin(); itr != varDefinitionMap.end(); ++itr) {
    varList += itr->first;
    varList += "=";
    std::ostringstream strs;
    strs << itr->second->getValue();
    std::string str = strs.str();
    varList += str;
    varList += ";";
  }
  return varList;
}
float expressionChecker(std::string value){
  std::string varList = createVarList();
  value = removeSpaces(value);

  Interpreter *interpreter = new Interpreter();
  Expression *exp = nullptr;
  interpreter->setVariables(varList.substr(0, varList.length() - 1));
  exp = interpreter->interpret(value);
  return exp->calculate();
}
pair<string,int> readUntilChar(std::list<std::string> lexer, string s){
  string retVal = "";
  int counter = 0;
  int x = -1;
  string oper = s;
  while(x== -1 &&  (oper == s)){
    retVal += lexer.front();
    lexer.pop_front();
    if(oper == "@") {
      oper = findNextOperator(lexer.front());
    }
    x=lexer.front().find(oper);
    counter++;
  }
  retVal += lexer.front().substr(0,x);
  return make_pair(retVal,counter);
}
string findNextOperator(string s){

  if(s == "<="){
    return "<=";
  } else if(s == ">="){
    return ">=";
  }
  else if(s == "=="){
    return "==";
  }
  else if(s == "<"){
    return "<";
  }
  else if(s == ">"){
    return ">";
  } else{
    return "@";
  }

}