#include "../../include/process/ComputingProcess.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

ComputingProcess::ComputingProcess(int id, const string& expr)
    : Process(id), expression(expr) {
    // ctor
}

ComputingProcess::~ComputingProcess() {
    // dtor
}

bool ComputingProcess::execute() {
    double left, right, result;
    char op;
    istringstream iss(expression);

    if (!(iss >> left >> op >> right)) {
        cout << "Expressão inválida: " << expression << endl;
        return false;
    }

    switch (op) {
    case '+': result = left + right; break;
    case '-': result = left - right; break;
    case '*': result = left * right; break;
    case '/':
        if (right == 0) {
            cout << "Erro: divisão por zero." << endl;
            return false;
        }
        result = left / right;
        break;
    default:
        cout << "Operador desconhecido: " << op << endl;
        return false;
    }

    cout << expression << " = " << result << endl;
    return true;
}

void ComputingProcess::printInfo() const {
    cout << "Expressão: " << expression << endl;
}

string ComputingProcess::toString() const {
    return "ComputingProcess: " + expression;
}

void ComputingProcess::printInfo() const {
    cout << "Método printInfo da classe ComputingProcess não implementado." << endl;
}

string ComputingProcess::toString() const {
    cout << "Método toString da classe ComputingProcess não implementado." << endl;
    return "";
}