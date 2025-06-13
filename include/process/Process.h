#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

using namespace std;

class Process {
    public:
        Process(int id) : pid(id) {};
        virtual ~Process() {};

        // Método vitual puro que deve ser implementado por todas as subclasses
        virtual bool execute() = 0;
        virtual void printInfo() const = 0;
        virtual string toString() const = 0;
        virtual string getType() const = 0;

        int getPID() const { return pid; }
        void setPID(int id) { pid = id; }

    protected:
        int pid; 

    private:

};

#endif // PROCESS_H