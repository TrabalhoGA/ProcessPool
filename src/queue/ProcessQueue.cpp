#include "queue/ProcessQueue.h"
#include <fstream>

using namespace std;

ProcessQueue::ProcessQueue() : front(nullptr), rear(nullptr), size(0) {
    // ctor
}

ProcessQueue::~ProcessQueue() {
    clear();
}

void ProcessQueue::enqueue(Process* process) {
    if (process == nullptr) {
        cerr << "Erro: Tentativa de adicionar processo nulo à fila." << endl;
        return;
    }
    
    ProcessNode* newNode = new ProcessNode(process);
    
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->setNext(newNode);
        rear = newNode;
    }
    
    size++;
}

Process* ProcessQueue::dequeue() {
    if (isEmpty()) {
        cerr << "Erro: Tentativa de remover de fila vazia." << endl;
        return nullptr;
    }
    
    ProcessNode* nodeToRemove = front;
    Process* process = nodeToRemove->getProcess();
    
    front = front->getNext();
    
    if (front == nullptr) {  
        rear = nullptr;
    }
    
    delete nodeToRemove;
    size--;
    
    return process;
}

Process* ProcessQueue::peek() const {
    if (isEmpty()) {
        return nullptr;
    }
    return front->getProcess();
}

Process* ProcessQueue::findByPID(int pid) const {
    ProcessNode* current = front;
    
    while (current != nullptr) {
        if (current->getProcess()->getPID() == pid) {
            return current->getProcess();
        }
        current = current->getNext();
    }
    
    return nullptr;
}

Process* ProcessQueue::removeByPID(int pid) {
    if (isEmpty()) {
        return nullptr;
    }
    
    if (front->getProcess()->getPID() == pid) {
        return dequeue();
    }
    
    ProcessNode* current = front;
    ProcessNode* previous = nullptr;
    
    while (current != nullptr && current->getProcess()->getPID() != pid) {
        previous = current;
        current = current->getNext();
    }
    
    if (current == nullptr) {
        return nullptr;
    }
    
    Process* process = current->getProcess();
    previous->setNext(current->getNext());
    
    if (current == rear) {
        rear = previous;
    }
    
    delete current;
    size--;
    
    return process;
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
        Process* process = dequeue();
        delete process;
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
    
    ProcessNode* current = front;
    int position = 1;
    
    while (current != nullptr) {
        cout << "Posição " << position << ": ";
        current->getProcess()->printInfo();
        cout << endl;
        
        current = current->getNext();
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