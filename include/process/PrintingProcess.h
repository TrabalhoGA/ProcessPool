#pragma once
#ifndef PRINTING_PROCESS_H
#define PRINTING_PROCESS_H

#include "Process.h"

using namespace std;

class PrintingProcess : public Process {
    public:
        PrintingProcess();
        virtual ~PrintingProcess();

        bool execute() override;

    protected:

    private:
};

#endif // PRINTING_PROCESS_H