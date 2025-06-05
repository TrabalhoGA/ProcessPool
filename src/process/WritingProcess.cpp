// WritingProcess.cpp
#include "process/WritingProcess.h"
#include <fstream>
#include <string>

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
    getline(cin, expression);

    writeExpression(expression);

    cout << "Expressão salva com sucesso em /data/computation.txt." << endl;
    return true;
}

void WritingProcess::printInfo() const {
    cout << "Método printInfo da classe WritingProcess não implementado." << endl;
}

string WritingProcess::toString() const {
    cout << "Método toString da classe WritingProcess não implementado." << endl;
    return "";
}