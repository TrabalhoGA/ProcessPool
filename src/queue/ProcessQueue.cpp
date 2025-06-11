#include "queue/ProcessQueue.h"
#include <fstream>
#include <memory>

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
    cout << "Método saveToFile não implementado ainda." << endl;
    return false;
}

bool ProcessQueue::loadFromFile(const string& filename) {
    cout << "Método loadFromFile não implementado ainda." << endl;
    return false;
}