#include "expression/Expression.h"
#include <sstream>
#include <stdexcept>

Expression::Expression() : operand1(0.0), operand2(0.0), operation('+') {
    // construtor padrão
}

Expression::Expression(double op1, char op, double op2) 
    : operand1(op1), operand2(op2), operation(op) {
    
    if (!isValidOperation(op)) {
        throw invalid_argument("Operação inválida! Use +, -, * ou /");
    }
}

Expression::Expression(const string& expr) {
    parseExpression(expr);
}

Expression::~Expression() {
    // dtor
}

void Expression::setOperation(char op) {
    if (!isValidOperation(op)) {
        throw invalid_argument("Operação inválida! Use +, -, * ou /");
    }
    operation = op;
}

double Expression::calculate() const {
    if (!isValid()) {
        throw runtime_error("Expressão inválida para cálculo!");
    }
    
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0.0) {
                throw runtime_error("Erro: Divisão por zero!");
            }
            return operand1 / operand2;
        default:
            throw runtime_error("Operação desconhecida!");
    }
}

string Expression::toString() const {
    ostringstream oss;
    oss << operand1 << " " << operation << " " << operand2;
    return oss.str();
}

bool Expression::isValid() const {
    return isValidOperation(operation) && 
           (operation != '/' || operand2 != 0.0);
}

bool Expression::isValidOperation(char op) const {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

void Expression::parseExpression(const string& expr) {
    istringstream iss(expr);
    
    if (!(iss >> operand1 >> operation >> operand2)) {
        throw invalid_argument("Formato de expressão inválido! Use: 'numero operacao numero'");
    }
    
    if (!isValidOperation(operation)) {
        throw invalid_argument("Operação inválida! Use +, -, * ou /");
    }
    
    string remaining;
    if (iss >> remaining) {
        throw invalid_argument("Formato de expressão inválido! Caracteres extras encontrados.");
    }
}

ostream& operator<<(ostream& os, const Expression& expr) {
    os << expr.toString();
    return os;
}