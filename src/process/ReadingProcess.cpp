#include "process/ReadingProcess.h"
#include "process/ComputingProcess.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

ReadingProcess::ReadingProcess(int id, ProcessQueue* queue)
    : Process(id), processQueue(queue) {
    // ctor
}

ReadingProcess::~ReadingProcess() {
    // dtor
}

bool ReadingProcess::execute() {
    if (!processQueue) {
        cout << "Fila de processos não definida." << endl;
        return false;
    }

    ifstream file("../data/computation.txt");
    if (!file.is_open()) {
        cout << "Não foi possível abrir o arquivo ../data/computation.txt" << endl;
        return false;
    }

    string line;
    int nextId = this->getPID() * 1000; // Geração de id único
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        ComputingProcess* proc = new ComputingProcess(nextId++, line);
        processQueue->enqueue(proc);
        count++;
    }
    file.close();

    // Limpa o conteúdo do arquivo
    ofstream clearFile("../data/computation.txt", ios::trunc);
    clearFile.close();

    cout << count << " processos de cálculo adicionados à fila e arquivo limpo." << endl;
    return count > 0;
}

void ReadingProcess::printInfo() const {
    cout << "Método printInfo da classe ReadingProcess não implementado." << endl;
}

string ReadingProcess::toString() const {
    cout << "Método toString da classe ReadingProcess não implementado." << endl;
    return "";
}