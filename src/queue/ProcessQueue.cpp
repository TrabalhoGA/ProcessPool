#include "queue/ProcessQueue.h"
#include "process/ComputingProcess.h"
#include "process/WritingProcess.h"
#include "process/ReadingProcess.h"
#include "process/PrintingProcess.h"
#include <fstream>
#include <memory>
#include <sstream>

using namespace std;

ProcessQueue::ProcessQueue() : front(nullptr), rear(nullptr), size(0), nextPID(1) {
    // ctor
}

ProcessQueue::~ProcessQueue() {
    clear();
}

int ProcessQueue::enqueue(Process* process) {
    if (process == nullptr) {
        cerr << "Erro: Tentativa de adicionar processo nulo à fila." << endl;
        return -1;
    }
    // Geração automática de PID único
    int pid = nextPID;
    while (findByPID(pid) != nullptr) {
        pid++;
    }
    nextPID = pid + 1;
    process->setPID(pid);
    auto newNode = make_unique<ProcessNode>(unique_ptr<Process>(process));
    if (isEmpty()) {
        front = move(newNode);
        rear = front.get();
    } else {
        rear->next = move(newNode);
        rear = rear->next.get();
    }
    size++;
    return pid;
}

Process* ProcessQueue::dequeue() {
    if (isEmpty()) {
        cerr << "Erro: Tentativa de remover de fila vazia." << endl;
        return nullptr;
    }
    auto nodeToRemove = move(front);
    Process* process = nodeToRemove->process.release();
    front = move(nodeToRemove->next);
    if (!front) {
        rear = nullptr;
    }
    size--;
    return process;
}

Process* ProcessQueue::peek() const {
    if (isEmpty()) {
        return nullptr;
    }
    return front->process.get();
}

Process* ProcessQueue::getProcessAt(int index) const {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    ProcessNode* current = front.get();
    int count = 0;
    while (current != nullptr && count < index) {
        current = current->next.get();
        count++;
    }
    if (current) {
        return current->process.get();
    }
    return nullptr;
}

Process* ProcessQueue::findByPID(int pid) const {
    ProcessNode* current = front.get();
    while (current != nullptr) {
        if (current->process->getPID() == pid) {
            return current->process.get();
        }
        current = current->next.get();
    }
    return nullptr;
}

Process* ProcessQueue::removeByPID(int pid) {
    if (isEmpty()) {
        return nullptr;
    }
    if (front->process->getPID() == pid) {
        return dequeue();
    }
    ProcessNode* previous = front.get();
    ProcessNode* current = front->next.get();
    while (current != nullptr && current->process->getPID() != pid) {
        previous = current;
        current = current->next.get();
    }
    if (current == nullptr) {
        return nullptr;
    }
    unique_ptr<ProcessNode> nodeToRemove = move(previous->next);
    previous->next = move(nodeToRemove->next);
    if (current == rear) {
        rear = previous;
    }
    size--;
    return nodeToRemove->process.release();
}

bool ProcessQueue::removeSpecific(Process* process) {
    if (process == nullptr || isEmpty()) {
        return false;
    }
    return removeByPID(process->getPID()) != nullptr;
}

bool ProcessQueue::isEmpty() const {
    return front == nullptr;
}

int ProcessQueue::getSize() const {
    return size;
}

void ProcessQueue::clear() {
    while (!isEmpty()) {
        unique_ptr<Process> process(dequeue());
    }
}

void ProcessQueue::printQueue() const {
    if (isEmpty()) {
        cout << "Fila de processos vazia." << endl;
        return;
    }
    cout << "=== FILA DE PROCESSOS ===" << endl;
    cout << "Total de processos: " << size << endl;
    cout << "-------------------------" << endl;
    ProcessNode* current = front.get();
    int position = 1;
    while (current != nullptr) {
        cout << "Posição " << position << ": ";
        current->process->printInfo();
        cout << endl;
        current = current->next.get();
        position++;
    }
    cout << "=========================" << endl;
}

bool ProcessQueue::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo para escrita: " << filename << endl;
        return false;
    }
    ProcessNode* current = front.get();
    while (current != nullptr) {
        Process* p = current->process.get();
        string type = p->getType();
        if (type == "ComputingProcess") {
            file << "ComputingProcess " << static_cast<ComputingProcess*>(p)->getExpression();
        } else if (type == "WritingProcess") {
            file << "WritingProcess";
        } else if (type == "ReadingProcess") {
            file << "ReadingProcess";
        } else if (type == "PrintingProcess") {
            file << "PrintingProcess";
        } else {
            file << "Unknown";
        }
        file << '\n';
        current = current->next.get();
    }
    file.close();
    return true;
}

bool ProcessQueue::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir arquivo para leitura: " << filename << endl;
        return false;
    }
    clear();
    string line;
    int linhasInvalidas = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string type;
        iss >> type;
        if (type == "ComputingProcess") {
            string expr;
            getline(iss, expr);
            if (!expr.empty() && expr[0] == ' ') expr = expr.substr(1);
            if (!expr.empty() && expr.front() == '"') expr = expr.substr(1, expr.size()-2);
            if (!expr.empty()) {
                ComputingProcess* p = new ComputingProcess(-1, expr);
                enqueue(p);
            } else {
                linhasInvalidas++;
            }
        } else if (type == "WritingProcess") {
            WritingProcess* p = new WritingProcess(-1);
            enqueue(p);
        } else if (type == "ReadingProcess") {
            ReadingProcess* p = new ReadingProcess(-1, this);
            enqueue(p);
        } else if (type == "PrintingProcess") {
            PrintingProcess* p = new PrintingProcess(-1, this);
            enqueue(p);
        } else {
            linhasInvalidas++;
        }
    }
    file.close();
    if (linhasInvalidas > 0) {
        cerr << "Aviso: " << linhasInvalidas << " linha(s) inválida(s) ignorada(s) ao carregar a fila." << endl;
    }
    return true;
}