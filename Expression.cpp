//
// Created by nahomamit on 11/11/2019.
//

//
// Created by galkam on 11/11/2019.
//
using namespace std;
#include <string>
#include <list>
#include <iostream>
#include "Expression.h"
#include "stack"
#include "queue"


class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;

  BinaryOperator(Expression *l, Expression *r) : Expression() {
    left = l;
    right = r;
  }
};

class Value : public Expression {
  float x;

  virtual float calculate() {
    return x;
  }

 public:
  Value(float num) : Expression() {
    x = num;
  }
};

class Variable : public Expression {
  std::string name;
  float value;

  Variable &operator--() {
    this->value--;
    return *this;
  }

  Variable &operator--(int) {
    this->value--;
    return *this;
  }
  Variable &operator+=(float dumy) {
    this->value+=dumy;
    return *this;
  }

  Variable &operator-=(float dumy) {
    this->value-=dumy;
    return *this;
  }

 public:
  Variable &operator++() {
    this->value++;
    return *this;
  }

  Variable &operator++(int) {
    this->value++;
    return *this;
  }
  virtual float calculate() {
    return value;
  }
  Variable() : Expression(){

  };
  Variable(std::string var, float num) : Expression() {
    name = var;
    value = num;
  }
  void setNumber(float x){
    this->value = x;
  }
  std::string getVariable(){
    return this->name;
  }

  float getNumber(){
    return this->value;
  }
};

class UnaryOperator : public Expression {
 protected:
  Expression *expression;

  UnaryOperator(Expression *expression1) : Expression() {
    expression = expression1;
  }
};

class Plus : public BinaryOperator {

  virtual float calculate() {
    return left->calculate() + right->calculate();
  }

 public:
  Plus(Expression *r, Expression *l) : BinaryOperator(r, l) {}
};

class Minus : public BinaryOperator {

  virtual float calculate() {
    return left->calculate() - right->calculate();
  }

 public:
  Minus(Expression *r, Expression *l) : BinaryOperator(r, l) {}
};

class Mul : public BinaryOperator {

  virtual float calculate() {
    return left->calculate() * right->calculate();
  }

 public:
  Mul(Expression *r, Expression *l) : BinaryOperator(r, l) {}
};

class Div : public BinaryOperator {

  virtual float calculate() {
    if (right->calculate() != 0)
      return left->calculate() / right->calculate();
    else
      throw ("Bad Input");
  }

 public:
  Div(Expression *r, Expression *l) : BinaryOperator(r, l) {}
};

class UPlus : public UnaryOperator {

  virtual float calculate() {
    return expression->calculate();
  }

 public:
  UPlus(Expression *expression1) : UnaryOperator(expression1) {}
};

class UMinus : public UnaryOperator {

  virtual float calculate() {
    return expression->calculate() * (-1);
  }

 public:
  UMinus(Expression *expression1) : UnaryOperator(expression1) {}
};



class Interpreter {
 protected:
  std::list<Variable*> arr;
  std::list<char> opers = {'+','-','*','/','(',')','_','@'};
  std::stack<char*> operators;
  std::stack<Expression*> expressions;
  std::queue<char> queue1;
  int semiCounter = 0;



 public:
  void setVariables(std::string s){
    s += ';';
    int end =  (signed)s.find(";");
    int start = 0;

    while (end<(signed)s.length() && end != -1) {
      int equals = s.substr(start).find("=");
      string variable = s.substr(start, equals);
      string number = s.substr(equals+1+start, end-1-start-equals);
      for(int i = 0 ; i < (signed)number.length(); i++){
        if('0' > number[i] || number[i] > '9'){
          if(number[i] == '-' && i==0){
            if(number.length() > 1) {
              continue;
            }
          }
        }
      }float num;
      try {
        num = stod(number);
      } catch (char*c) {
        cout<<"maniak"<<std::endl;
      }
      checkVariable(variable,num);
      start = end+1;
      end = s.find(";", start, 1);

    }
  }
  void checkVariable(string name, float num){
    for (Variable* v :arr){
      if(v->getVariable().compare(name) == 0){
        v->setNumber(num);
        return;
      }
    }
    Variable *temp = new Variable(name, num);
    arr.push_back(temp);
  }
  Expression* interpret(string exp) {
    createExpression(exp);
    while (!queue1.empty()) {
      if (isOperator(queue1.front())) {
        operatorsFix(&queue1.front());
        queue1.pop();
      } else if(isVariable(exp.length() + semiCounter - queue1.size(), exp,1)) {
        // expressions.push(new Value(getVariable(queue1.front())));

      } else {
        buildNumber();
        semiCounter--;
      }
    }
    while(!operators.empty()){
      addOperator(*operators.top());
    }
    if(expressions.size() == 1) {
      return expressions.top();
    } else {
      throw ("bad input");
    }
  }
  void buildNumber(){
    string temp;
    while(queue1.front() != ';') {
      temp += queue1.front();
      queue1.pop();
    }
    queue1.pop();
    expressions.push(new Value(stod(temp)));


  }

  void operatorsFix(char* c){
    if(*c == '(') {
      operators.push(c);
    } else if(*c == ')'){
      while (*operators.top() != '(') {
        addOperator(*operators.top());

      }
      operators.pop();
    } else if (!biggerOperator(*c)) {
      addOperator(*operators.top());
      operators.push(c);
    } else {
      operators.push(c);
    }
  }
  void addOperator(char c) {
    operators.pop();
    if(c == ')' || c== '('){
      queue1.pop();
      return;
    }
    Expression* right = expressions.top();
    expressions.pop();
    Expression* left;
    if(expressions.empty() && (!queue1.empty()))
      if(queue1.front() != ')'){
        if(queue1.front() >= '1'&& queue1.front()<='9')
          buildNumber();
      }
    switch(c) {
      case '_' :
        expressions.push(new UMinus(right));
        break;
      case '@' :
        expressions.push(new UPlus(right));
        break;
      case '-' :
        left = expressions.top();
        expressions.pop();
        expressions.push(new Minus(left, right));
        break;
      case '+' :
        left = expressions.top();
        expressions.pop();
        expressions.push(new Plus(left, right));
        break;
      case '*' :
        left = expressions.top();
        expressions.pop();
        expressions.push(new Mul(left, right));
        break;
      case '/' :
        left = expressions.top();
        expressions.pop();
        expressions.push(new Div(left, right));
        break;
      default:
        break;
    }
  }
  void createExpression(string s){
    int sograim = 0;
    bool stillNumber = false;
    for(int i = 0; i < (signed)s.length(); i ++) {
      if(isOperator(s[i]) || isVariable(i,s) !=- 1) {
        if (stillNumber == true) {
          queue1.push(';');
          semiCounter++;
        }
        int x = isVariable(i,s);
        if(x != -1){
          for(int j = 0; j<x; j++){
            queue1.push(s[i]);
            i++;
          }
          i--;
          continue;
        }
        stillNumber = false;
        if(s[i] == '-'){
          if(i == 0||s.at(i-1)== '(' ){
            queue1.push('_');
          }
          else
            queue1.push('-');
        } else if(s[i] == '+'){
          if(i == 0 || s.at(i-1) == '(' ){
            queue1.push('@');
          }
          else
            queue1.push('+');
        } else {
          if(s.at(i) == '('){
            sograim++;
          } else if (s.at(i) == ')'){
            sograim--;
          }
          queue1.push(s.at(i));
        }
      } else {
        if(('0' <= s.at(i) && '9'>=s.at(i)) || (s.at(i) == '.')) {
          queue1.push(s.at(i));
          stillNumber = true;
        }
        else{
          throw ("error");
        }
      }
    }
    if(stillNumber == true){
      queue1.push(';');
      semiCounter++;
    }
    if(sograim != 0){
      throw ("bad input");
    }
  }

  bool isOperator(char c){
    for(char s : opers){
      if(c == s){
        return true;
      }
    }
    return false;
  }

  bool isVariable(int pos, string e, int checker){
    for(Variable* v : arr) {
      string temp = e.substr(pos, v->getVariable().length());
      if(v->getVariable()== temp){
        if(checker ==1) {
          expressions.push(new Value(getVariable(temp)));
          for (int i = 0; i < (signed)v->getVariable().length(); i++) {
            queue1.pop();
          }
        }
        return true;
      }
    }
    return false;
  }
  int isVariable(int pos, string e){
    for(Variable* v : arr) {
      string temp = e.substr(pos, v->getVariable().length());
      if(v->getVariable()== temp)
        return v->getVariable().size();
    }
    return -1;
  }
  float getVariable(string c){
    for(Variable* v : arr) {
      if(v->getVariable() == c){
        return v->getNumber();
      }
    }
    throw ("Bad Input");

  }
  bool biggerOperator(char new1) {
    if (operators.empty()) {
      return true;
    }
    char current = *operators.top();
    if (current == '(') {
      return true;
    }
    if (new1 == '_' || new1 == '@') {
      return true;
    }
    switch (new1) {
      case ('+') : {
        if (current == '*' || current == '/' ) {
          return true;
        } else {
          return false;
        }
      }
      case ('-') : {
        if (current == '*' || current == '/') {
          return true;
        } else {
          return false;
        }
      }
      case ('/') : {
        if (current == '+' || current == '-') {
          return false;
        } else {
          return true;
        }
      }
      case ('*') : {
        if (current == '+' || current == '-') {
          return true;
        } else {
          return false;
        }
      }
      default:
        return true;
    }
  }
};







