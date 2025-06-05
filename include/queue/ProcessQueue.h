#pragma once
#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include "process/Process.h"
#include <iostream>

using namespace std;

class ProcessQueue {
private:
    // Classe interna para nó da fila
    class ProcessNode {
    public:
        Process* process;
        ProcessNode* next;
        ProcessNode(Process* proc) : process(proc), next(nullptr) {}
        ~ProcessNode() { process = nullptr; next = nullptr; }
    };

    ProcessNode* front;
    ProcessNode* rear;
    int size;

public:
    ProcessQueue();
    virtual ~ProcessQueue();
    
    void enqueue(Process* process);
    Process* dequeue();
    Process* peek() const;
    
    Process* findByPID(int pid) const;
    Process* removeByPID(int pid);
    bool removeSpecific(Process* process);
    
    bool isEmpty() const;
    int getSize() const;
    void clear();
    
    void printQueue() const;
    
    bool saveToFile(const string& filename) const;
    bool loadFromFile(const string& filename);
    
    // Desabilita cópia e atribuição
    ProcessQueue(const ProcessQueue& other) = delete; 
    ProcessQueue& operator=(const ProcessQueue& other) = delete;
};

#endif // PROCESSQUEUE_H