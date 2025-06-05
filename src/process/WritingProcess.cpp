// WritingProcess.cpp
#include "process/WritingProcess.h"

using namespace std;

WritingProcess::WritingProcess(int id) : Process(id) {
    // ctor
}

WritingProcess::~WritingProcess() {
    // dtor
}

bool WritingProcess::execute() {
    cout << "Método execute da classe WritingProcess não implementado." << endl;
    return false;
}

void WritingProcess::printInfo() const {
    cout << "Método printInfo da classe WritingProcess não implementado." << endl;
}

string WritingProcess::toString() const {
    cout << "Método toString da classe WritingProcess não implementado." << endl;
    return "";
}