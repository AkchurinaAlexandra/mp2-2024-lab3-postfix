// реализация пользовательского приложения

#include <iostream>
#include <string>
#include "arithmetic.h"

int main() {
    std::string expression;
    std::cout << "Format:\n "
                 "1. Supported operators: +, -, ~(unary minus), *, /, sin, cos\n "
                 "2. Variables are supported\n "
                 "3. Brackets are supported\n "
                 "4. Unary minus is supported (- or ~)\n"
                 "5. Change of variable's value is not allowed";

    std::cout << "Enter the expression: ";
    std::getline(std::cin, expression);

    TPostfix postfix(expression);

    char choice;
    do {
        std::cout << "Do you want to set a variable? (y/n): ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            std::string var;
            double value;
            std::cout << "Enter variable name: ";
            std::cin >> var;
            std::cout << "Enter variable value: ";
            std::cin >> value;
            postfix.setVariable(var, value);
        }
    } while (choice == 'y' || choice == 'Y');

    try {
        postfix.toPostfix();
        double result = postfix.evaluate();
        std::cout << "The result is: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}