#include "process/PrintingProcess.h"
#include <sstream>

using namespace std;

PrintingProcess::PrintingProcess(int id, ProcessQueue* queue)
    : Process(id), processQueue(queue) {
}

PrintingProcess::~PrintingProcess() {
    // dtor
}

bool PrintingProcess::execute() {
    if (!processQueue) {
        cout << "Fila de processos não definida." << endl;
        return false;
    }
    processQueue->printQueue();
    return true;
}

void PrintingProcess::printInfo() const {
    cout << "=== PrintingProcess ===" << endl;
    cout << "PID: " << getPID() << endl;
    if (processQueue) {
        cout << "Tamanho atual da fila de processos: " << processQueue->getSize() << endl;
    } else {
        cout << "Fila de processos não definida." << endl;
    }
}

string PrintingProcess::toString() const {
    ostringstream oss;
    oss << "PrintingProcess[PID=" << getPID();
    if (processQueue) {
        oss << ", Fila tamanho=" << processQueue->getSize();
    } else {
        oss << ", Fila não definida";
    }
    oss << "]";
    return oss.str();
}