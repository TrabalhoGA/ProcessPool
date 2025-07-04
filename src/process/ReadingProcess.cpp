#include "process/ReadingProcess.h"
#include "process/ComputingProcess.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>
#ifdef _WIN32
    #include <direct.h>
#endif

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

    struct stat buffer;
    if (stat("data/computation.txt", &buffer) != 0) {
        return false;
    }

    ifstream file("data/computation.txt");
    if (!file.is_open()) {
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        ComputingProcess* proc = new ComputingProcess(-1, line); // PID será atribuído pela fila
        int pid = processQueue->enqueue(proc);
        count++;
    }
    file.close();

    ofstream clearFile("data/computation.txt", ios::trunc);
    clearFile.close();

    cout << count << " processos de cálculo adicionados à fila." << endl;
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