#include "../../include/process/ComputingProcess.h"

using namespace std;

ComputingProcess::ComputingProcess(int id) : Process(id) {
    // ctor
}

ComputingProcess::~ComputingProcess() {
    // dtor
}

bool ComputingProcess::execute() {
    cout << "Método execute da classe ComputingProcess não implementado." << endl;
    return false;
}

void ComputingProcess::printInfo() const {
    cout << "Método printInfo da classe ComputingProcess não implementado." << endl;
}

string ComputingProcess::toString() const {
    cout << "Método toString da classe ComputingProcess não implementado." << endl;
    return "";
}