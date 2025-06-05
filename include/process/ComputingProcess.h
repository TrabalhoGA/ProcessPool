#pragma once
#ifndef COMPUTINGPROCESS_H
#define COMPUTINGPROCESS_H

#include "Process.h"

using namespace std;

class ComputingProcess : public Process {
    public:
        ComputingProcess(int id);
        virtual ~ComputingProcess();

        bool execute() override;
        void printInfo() const override;
        string toString() const override;

    protected:

    private:
};

#endif // COMPUTINGPROCESS_H