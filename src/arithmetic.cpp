// ���������� ������� � ������� ��� ���������� �������������� ���������

#include "arithmetic.h"

TPostfix::TPostfix(const std::string& expr) : infix(expr) {}

void TPostfix::setVariable(const std::string& var, double value) {
    varNames.push_back(var);
    varValues.push_back(value);
}

std::string TPostfix::getPostfix() {
    return postfix;
}

int TPostfix::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "sin" || op == "cos" || op == "~") return 3;
    return 0;
}

double TPostfix::getVariableValue(const std::string& var) {
    for (size_t i = 0; i < varNames.get_size(); i++) {
        if (varNames[i] == var) return varValues[i];
    }
    throw std::runtime_error("Unknown variable: " + var);
}

bool TPostfix::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '~';
}

bool TPostfix::isPrefix(const std::string& s) {
    return s == "sin" || s == "cos" || s == "~";
}

void TPostfix::toPostfix() {
    postfix = "";
    TStack<std::string> stack;
    std::string token;
    bool unary = true; // ����� �� ��������� ����� �������
    for (size_t i = 0; i < infix.size(); i++) {
        if (isdigit(infix[i]) || isalpha(infix[i]) || (i != 0 && (infix[i - 1] == 'e' || infix[i - 1] == 'E'))) {
            token += infix[i];
        } else {
            if (!token.empty()) {
                if (isPrefix(token)) {
                    stack.push(token);
                    unary = true;
                } else {
                    postfix += token + " ";
                    unary = false;
                }
                token.clear();
            }
            if (infix[i] == '(') {
                stack.push("(");
                unary = true;
            } else if (infix[i] == ')') {
                while (!stack.empty() && stack.top() != "(") {
                    postfix += stack.top() + " ";
                    stack.pop();
                }
                if (stack.empty() || stack.top() != "(") {
                    throw std::logic_error("Mismatched parentheses");
                }
                stack.pop();
                if (!stack.empty() && isPrefix(stack.top())) {
                    postfix += stack.top() + " ";
                    stack.pop();
                }
                unary = false;
            } else if (isOperator(infix[i])) {

                if ((infix[i] == '-' || infix[i] == '~') && unary) {
                    stack.push("~");
                    continue;
                }

                std::string op(1, infix[i]);
                while (!stack.empty() && precedence(stack.top()) >= precedence(op)) {
                    postfix += stack.top() + " ";
                    stack.pop();
                }
                stack.push(op);
                unary = true;
            } else if (!isspace(infix[i])) {
                throw std::logic_error("Invalid character in expression: " + std::string(1, infix[i]));
            }
        }
    }
    if (!token.empty()) postfix += token + " ";
    while (!stack.empty()) {
        if (!isPrefix(stack.top()) && !isOperator(stack.top()[0])) {
            throw std::logic_error("Mismatched parentheses");
        }
        postfix += stack.top() + " ";
        stack.pop();
    }
}

double TPostfix::evaluate() {
    TStack<double> stack;
    std::string token;
    for (size_t i = 0; i < postfix.size(); i++) {
        if (postfix[i] != ' ') {
            token += postfix[i];
        } else {
            if (!token.empty()) {
                if (isdigit(token[0])) {
                    stack.push(custom_stod(token));
                } else if (isPrefix(token)) {
                    if (stack.empty()) {
                        throw std::logic_error("Insufficient operands for function: " + token);
                    }
                    double a = stack.pop();
                    if (token == "sin") stack.push(sin(a));
                    if (token == "cos") stack.push(cos(a));
                    if (token == "~") stack.push(-a);
                } else if (isalpha(token[0])) {
                    stack.push(getVariableValue(token));
                } else {
                    if (stack.size() < 2) {
                        throw std::logic_error("Insufficient operands for operator: " + token);
                    }
                    double b = stack.pop();
                    double a = stack.pop();
                    if (token == "+") stack.push(a + b);
                    else if (token == "-") stack.push(a - b);
                    else if (token == "*") stack.push(a * b);
                    else if (token == "/") stack.push(a / b);
                }
                token.clear();
            }
        }
    }
    if (stack.size() != 1) {
        throw std::logic_error("Invalid expression");
    }
    return stack.top();
}
double TPostfix::custom_stod(const std::string &str){
    size_t e_pos = str.find_first_of("eE");
    std::string mantissa_str = str;
    std::string exponent_str = "0";

    if (e_pos != std::string::npos) {
        mantissa_str = str.substr(0, e_pos);
        exponent_str = str.substr(e_pos + 1);
    }

    double mantissa = 0.0;
    double factor = 1.0;
    bool decimal_point = false;
    bool negative = false;
    size_t i = 0;

    if (mantissa_str[i] == '-') {
        negative = true;
        i++;
    } else if (mantissa_str[i] == '+') {
        i++;
    }

    for (; i < mantissa_str.size(); i++) {
        if (mantissa_str[i] == '.') {
            decimal_point = true;
            continue;
        }
        if (mantissa_str[i] < '0' || mantissa_str[i] > '9') {
            throw std::invalid_argument("Invalid character in mantissa");
        }
        if (decimal_point) {
            factor /= 10.0;
            mantissa += (mantissa_str[i] - '0') * factor;
        } else {
            mantissa = mantissa * 10.0 + (mantissa_str[i] - '0');
        }
    }

    if (negative) {
        mantissa = -mantissa;
    }

    int exponent = 0;
    negative = false;
    i = 0;

    if (exponent_str[i] == '-') {
        negative = true;
        i++;
    } else if (exponent_str[i] == '+') {
        i++;
    }

    for (; i < exponent_str.size(); i++) {
        if (!isdigit(exponent_str[i])) {
            throw std::invalid_argument("Invalid character in exponent");
        }
        exponent = exponent * 10 + (exponent_str[i] - '0');
    }

    if (negative) {
        exponent = -exponent;
    }

    return mantissa * std::pow(10, exponent);
