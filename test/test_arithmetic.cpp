#include <gtest.h>
#include <cmath>
#include "arithmetic.h"

// Visual Studio 
#ifndef M_PI  
    #define M_PI 3.14159265358979323846
#endif

const double EPS = 1e-6; // точность сравнения вещественных чисел

// Нельзя посчитать значение выражения, которое еще не переведено в постфиксную форму
TEST(TPostfix, cant_evaluate_before_postfix_method) {
    TPostfix d("0");
    ASSERT_ANY_THROW(d.evaluate());
}

TEST(TPostfix, test_bad_brackets) {
	TPostfix expr("3 + (1) * (3))");
	ASSERT_ANY_THROW(expr.toPostfix());
}

TEST(TPostfix, test_bad_expression) {
	TPostfix expr("3 + 1 1");
	expr.toPostfix();
	ASSERT_ANY_THROW(expr.evaluate());
}


TEST(TPostfix, convert_simple_expression_no_throw) {
	TPostfix d("1 + 1  + 1 *(2+3)");
	ASSERT_NO_THROW(d.toPostfix());
}

// Проверка что постфиксная запись правильно построилась
TEST(TPostfix, convert_to_postfix) {
    TPostfix d("1 + (2 * 3 + 4)");
    d.toPostfix();
    ASSERT_EQ("1 2 3 * 4 + + ", d.getPostfix());
}

// Проверка что подсчет значения выражения не выдаст исключений
TEST(TPostfix, evaluate_simple_expression) {
    TPostfix d("1 + 1  + 1 *(2+3)");
    d.toPostfix();
    ASSERT_NO_THROW(d.evaluate());
}

// Тест перевода в постфиксную запись
TEST(TPostfix, convert_to_postfix_simple) {
    TPostfix expr("3+5*2");
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 13, EPS);
}

TEST(TPostfix, test_unary_minus) {
    TPostfix d("-1");
    d.toPostfix();
    ASSERT_NEAR(d.evaluate(), -1, EPS);
}

TEST(TPostfix, complex_unary_minus) {
    TPostfix d("1 + -1 - (-5 + 3) * -2 + -(-1) - - - 5");
    d.toPostfix();
    ASSERT_NEAR(d.evaluate(), 1 + -1 - (-5 + 3) * -2 + -(-1) - - - 5, EPS);
}

TEST(TPostfix, test_expression_with_unary_minus) {
    TPostfix d("3 + - 1");
    d.toPostfix();
    ASSERT_NEAR(d.evaluate(), 2, EPS);
}

TEST(TPostfix, test_expression_with_double_unary_minus) {
    TPostfix d("3 + - - 1");
    d.toPostfix();
    ASSERT_NEAR(d.evaluate(), 4, EPS);
}

TEST(TPostfix, convert_to_postfix_with_brackets) {
    TPostfix expr("(3+5)*2");
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 16, EPS);
}

TEST(TPostfix, convert_to_postfix_with_variables) {
    TPostfix expr("a+b*c");
    expr.setVariable("a", 4);
    expr.setVariable("b", 5);
    expr.setVariable("c", 2);
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 14, EPS);
}


TEST(TPostfix, test_with_no_variables) {
	TPostfix expr("3 + x * 2"); 
    expr.toPostfix();
	ASSERT_ANY_THROW(expr.evaluate());
}


// Тест работы с переменными
TEST(TPostfix, evaluate_with_variables) {
    TPostfix expr("x*y+z");
    expr.setVariable("x", 2);
    expr.setVariable("y", 3);
    expr.setVariable("z", 4);
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 10, EPS);
}

// Тест вычисления тригонометрических функций
TEST(TPostfix, evaluate_simple_cos) {
    TPostfix expr("cos 0");
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 1, EPS); // cos(0) = 1
}

TEST(TPostfix, evaluate_sin_with_minus) {
    TPostfix expr("sin -x");
	expr.toPostfix();
	expr.setVariable("x", M_PI / 2);
    ASSERT_NEAR(expr.evaluate(), -1, EPS); // sin(pi/2) = 1, cos(0) = 1, 1 + 1 = 2
}

TEST(TPostfix, evaluate_sin_cos) {
	TPostfix expr("sin(x) + cos(y)");
	expr.toPostfix();
	expr.setVariable("x", M_PI / 2);
	expr.setVariable("y", 0);
	ASSERT_NEAR(expr.evaluate(), 2, EPS); // sin(pi/2) = 1, cos(0) = 1, 1 + 1 = 2
}

TEST(TPostfix, evaluate_complex_expression) {
    TPostfix expr("sin(a) * cos(b) + c");
    expr.setVariable("a", M_PI / 4);
    expr.setVariable("b", M_PI / 4);
    expr.setVariable("c", 2);
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 2.5, EPS); // sin(pi/4) * cos(pi/4) + 2
}

TEST(TPostfix, evaluate_with_nested_functions) {
    TPostfix expr("sin(sin(0) + x)");
    expr.setVariable("x", M_PI);
    expr.toPostfix();
    // sin(sin(0) + pi) = sin(0 + pi) = sin(pi) = 0
    ASSERT_NEAR(expr.evaluate(), 0, EPS);
}

TEST(TPostfix, evaluate_with_exponential_notation) {
    TPostfix expr("1e5");
    expr.toPostfix();
    ASSERT_NEAR(expr.evaluate(), 1e5, EPS);
}

TEST(TPostfix, evaluate_with_negative_exponential_notation) {
	TPostfix expr("1e-3");
	expr.toPostfix();
	ASSERT_NEAR(expr.evaluate(), 1e-3, EPS);
}

