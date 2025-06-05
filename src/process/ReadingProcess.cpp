#include "process/ReadingProcess.h"

using namespace std;

ReadingProcess::ReadingProcess(int id) : Process(id) {
    // ctor
}

ReadingProcess::~ReadingProcess() {
    // dtor
}

bool ReadingProcess::execute() {
    cout << "Método execute da classe ReadingProcess não implementado." << endl;
    return false;
}

void ReadingProcess::printInfo() const {
    cout << "Método printInfo da classe ReadingProcess não implementado." << endl;
}

string ReadingProcess::toString() const {
    cout << "Método toString da classe ReadingProcess não implementado." << endl;
    return "";
}