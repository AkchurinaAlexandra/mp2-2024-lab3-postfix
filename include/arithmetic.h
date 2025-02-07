#pragma once
#include "stack.h"
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>

class TPostfix {
 private:
    std::string infix;      // "3 + 2 * 10"
    std::string postfix;    // "3 2 10 * +"
    TVector<std::string> varNames;
    TVector<double> varValues;

    static int precedence(const std::string& op);
    double getVariableValue(const std::string& var);
    static bool isOperator(char c);
    static bool isPrefix(const std::string& s);

    static double custom_stod(const std::string& str);

 public:
    TPostfix(const std::string& expr);
    void setVariable(const std::string& var, double value);
    std::string getPostfix();
    void toPostfix();
    double evaluate();
};