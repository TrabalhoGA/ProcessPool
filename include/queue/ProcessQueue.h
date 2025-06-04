#pragma once
#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include "ProcessNode.h"
#include "../process/Process.h"
#include <iostream>

class ProcessQueue {
private:
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
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    // Desabilita cópia e atribuição
    ProcessQueue(const ProcessQueue& other) = delete; 
    ProcessQueue& operator=(const ProcessQueue& other) = delete;
};

#endif // PROCESSQUEUE_H