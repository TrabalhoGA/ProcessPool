#include "../../include/process/ComputingProcess.h"
#include "../../include/expression/Expression.h"
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
    Expression exprEvaluator;
    try {
        double result = exprEvaluator.evaluate(expression);
        cout << expression << " = " << result << endl;
        return true;
    } catch (const std::exception& e) {
        cout << "Erro ao avaliar expressão: " << e.what() << endl;
        return false;
    }
}

void ComputingProcess::printInfo() const {
    cout << "Expressão: " << expression << endl;
}

string ComputingProcess::toString() const {
    return "ComputingProcess: " + expression;
}