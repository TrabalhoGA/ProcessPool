#pragma once
#ifndef PROCESSNODE_H
#define PROCESSNODE_H

#include "../process/Process.h"

class ProcessNode {
    private:
        Process* process;
        ProcessNode* next;

    public:
        // Construtor
        ProcessNode(Process* proc);
        
        // Destrutor
        ~ProcessNode();
        
        // Getters
        Process* getProcess() const;
        ProcessNode* getNext() const;
        
        // Setters
        void setNext(ProcessNode* nextNode);
        
        // Classe ProcessQueue precisa acessar os membros privados
        friend class ProcessQueue;
};

#endif // PROCESSNODE_H