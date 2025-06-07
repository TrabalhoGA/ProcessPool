#pragma once
#ifndef PRINTING_PROCESS_H
#define PRINTING_PROCESS_H

#include "Process.h"
#include "queue/ProcessQueue.h"

using namespace std;

class PrintingProcess : public Process {
    public:
        PrintingProcess(int id, ProcessQueue* queue);
        virtual ~PrintingProcess();

        bool execute() override;
        void printInfo() const override;
        string toString() const override;

    protected:

    private:
		ProcessQueue* processQueue;
};

#endif // PRINTING_PROCESS_H