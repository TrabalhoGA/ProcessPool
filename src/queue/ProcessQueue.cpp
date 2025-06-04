#include "../include/queue/ProcessQueue.h"
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
        std::cerr << "Erro: Tentativa de adicionar processo nulo à fila." << std::endl;
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
        std::cerr << "Erro: Tentativa de remover de fila vazia." << std::endl;
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
        std::cout << "Fila de processos vazia." << std::endl;
        return;
    }
    
    std::cout << "=== FILA DE PROCESSOS ===" << std::endl;
    std::cout << "Total de processos: " << size << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    ProcessNode* current = front;
    int position = 1;
    
    while (current != nullptr) {
        std::cout << "Posição " << position << ": ";
        // Aqui você pode chamar um método toString() do Process
        // ou implementar a lógica de impressão específica
        current->getProcess()->printInfo();
        std::cout << std::endl;
        
        current = current->getNext();
        position++;
    }
    
    std::cout << "=========================" << std::endl;
}

void ProcessQueue::saveToFile(const std::string& filename) const {
    cout << "Método saveToFile não implementado ainda." << endl;
}

void ProcessQueue::loadFromFile(const std::string& filename) {
    cout << "Método loadFromFile não implementado ainda." << endl;
}