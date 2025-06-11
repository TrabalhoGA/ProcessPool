#include "process/WritingProcess.h"
#include <fstream>
#include <string>
#include <limits>

using namespace std;

WritingProcess::WritingProcess(int id) : Process(id) {
    // ctor
}

WritingProcess::~WritingProcess() {
    // dtor
}

bool WritingProcess::writeExpression(const string& expression) {
    ofstream file("data/computation.txt", ios::app);
    if (file.is_open()) {
        file << expression << '\n';
        file.close();
        return true;
    }
    return false;
}

bool WritingProcess::execute() {
    cout << "Digite a expressão matemática para salvar em computation.txt: ";
    string expression;

    if (cin.rdbuf()->in_avail() > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin >> expression;
    if (expression.empty()) {
        cout << "Nenhuma expressão foi digitada." << endl;
        return false;
    }

    if (!writeExpression(expression)) {
        cout << "Erro ao escrever a expressão no arquivo." << endl;
        return false;
    }

    cout << "Expressão salva com sucesso em computation.txt." << endl;
    return true;
}

void WritingProcess::printInfo() const {
    cout << "=== WritingProcess ===" << endl;
    cout << "PID: " << getPID() << endl;
}

string WritingProcess::toString() const {
    return "WritingProcess[PID=" + to_string(getPID()) + "]";
}