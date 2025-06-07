#include "process/PrintingProcess.h"

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
    cout << "=== Fila de Processos ===" << endl;
    processQueue->printQueue();
    return true;
}

void PrintingProcess::printInfo() const {
    cout << "Método printInfo da classe PrintingProcess não implementado." << endl;
}

string PrintingProcess::toString() const {
    cout << "Método toString da classe PrintingProcess não implementado." << endl;
    return "";
}