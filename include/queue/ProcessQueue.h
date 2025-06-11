#pragma once
#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include "process/Process.h"
#include <iostream>
#include <memory>

using namespace std;

class ProcessQueue {
private:
    // Classe interna para nó da fila
    class ProcessNode {
    public:
        unique_ptr<Process> process;
        unique_ptr<ProcessNode> next;
        ProcessNode(unique_ptr<Process> proc) : process(move(proc)), next(nullptr) {}
        ~ProcessNode() = default;
    };

    unique_ptr<ProcessNode> front;
    ProcessNode* rear;
    int size;
    int nextPID;

public:
    ProcessQueue();
    virtual ~ProcessQueue();
    int enqueue(Process* process); 
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