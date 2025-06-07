// WritingProcess.cpp
#include "process/WritingProcess.h"
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void WritingProcess::writeExpression(const string& expression) {
    // Caminho relativo para o arquivo computation.txt na pasta /data
    ofstream file("../data/computation.txt", ios::app);
    if (file.is_open()) {
        file << expression << '\n';
        file.close();
    }
    else {
        // Opcional: tratamento de erro simples
        // Você pode adicionar logging ou lançar exceção se preferir
    }
}

WritingProcess::WritingProcess(int id) : Process(id) {
    // ctor
}

WritingProcess::~WritingProcess() {
    // dtor
}

bool WritingProcess::execute() {
    cout << "Digite a expressão matemática para salvar em computation.txt: ";
    string expression;

    // Limpa o buffer de entrada, se necessário
    if (cin.rdbuf()->in_avail() > 0)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, expression);

    writeExpression(expression);

    cout << "Expressão salva com sucesso em /data/computation.txt." << endl;
    return true;
}

void WritingProcess::printInfo() const {
    cout << "=== WritingProcess ===" << endl;
    cout << "PID: " << getPID() << endl;
}

string WritingProcess::toString() const {
    return "WritingProcess[PID=" + to_string(getPID()) + "]";
}