//
// Created by nahomamit on 26/12/2019.
//

#ifndef FLIGHTSIMULATORGAL__EXPRESSION_H_
#define FLIGHTSIMULATORGAL__EXPRESSION_H_

#endif //FLIGHTSIMULATORGAL__EXPRESSION_H_

class Expression {

 public:
  virtual float calculate() = 0;
  virtual ~Expression() {}
};


class ex1 {
  class BinaryOperator : public Expression {};
  class Value : public BinaryOperator{};
  class Variable : public Expression {};
  class UnaryOperator : public Expression {};
  class Plus : public BinaryOperator {};
  class Minus : public BinaryOperator {};
  class Mul : public BinaryOperator {};
  class Div : public BinaryOperator {};
  class UPlus : public UnaryOperator {};
  class UMinus : public UnaryOperator {};
  class Interpreter;
 public:
};