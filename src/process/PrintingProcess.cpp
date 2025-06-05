#include "process/PrintingProcess.h"

using namespace std;

PrintingProcess::PrintingProcess(int id) : Process(id) {
    // ctor
}

PrintingProcess::~PrintingProcess() {
    // dtor
}

bool PrintingProcess::execute() {
    cout << "Método execute da classe PrintingProcess não implementado." << endl;
    return false;
}

void PrintingProcess::printInfo() const {
    cout << "Método printInfo da classe PrintingProcess não implementado." << endl;
}

string PrintingProcess::toString() const {
    cout << "Método toString da classe PrintingProcess não implementado." << endl;
    return "";
}