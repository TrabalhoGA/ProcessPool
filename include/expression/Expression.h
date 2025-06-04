#pragma once
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>

using namespace std;

class Expression {
    public:
        // Construtores
        Expression();
        Expression(double op1, char op, double op2);
        Expression(const string& expr);

        // Destrutor
        virtual ~Expression();

        // Getters
        double getOperand1() const { return operand1; }
        double getOperand2() const { return operand2; }
        char getOperation() const { return operation; }

        // Setters
        void setOperand1(double op1) { operand1 = op1; }
        void setOperand2(double op2) { operand2 = op2; }
        void setOperation(char op);

        // Método principal
        double calculate() const;

        // Utilitários
        string toString() const;
        bool isValid() const;

        // Sobrecarga de operadores
        friend ostream& operator<<(ostream& os, const Expression& expr);

    protected:

    private:
        double operand1;
        double operand2;
        char operation;

        void parseExpression(const string& expr);
        bool isValidOperation(char op) const;
};

#endif // EXPRESSION_H
        