#pragma once
#ifndef COMPUTINGPROCESS_H
#define COMPUTINGPROCESS_H

#include "Process.h"

using namespace std;

class ComputingProcess : public Process {
    public:
        ComputingProcess();
        virtual ~ComputingProcess();

        bool execute() override;

    protected:

    private:
};

#endif // COMPUTINGPROCESS_H