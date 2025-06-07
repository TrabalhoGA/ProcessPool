#include "process/ReadingProcess.h"
#include "process/ComputingProcess.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <direct.h>

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

    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
        cout << "Diretório de trabalho: " << cwd << endl;
    }

    struct stat buffer;
    if (stat("../data/computation.txt", &buffer) != 0) {
        cout << "Arquivo ../data/computation.txt não existe!" << endl;
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
    cout << "=== ReadingProcess ===" << endl;
    cout << "PID: " << getPID() << endl;
    if (processQueue) {
        cout << "Tamanho atual da fila de processos: " << processQueue->getSize() << endl;
    } else {
        cout << "Fila de processos não definida." << endl;
    }
}

string ReadingProcess::toString() const {
    string result = "ReadingProcess[PID=" + to_string(getPID());
    if (processQueue) {
        result += ", Fila tamanho=" + to_string(processQueue->getSize());
    }
    else {
        result += ", Fila não definida";
    }
    result += "]";
    return result;
}