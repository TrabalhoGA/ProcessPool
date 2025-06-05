#pragma once
#ifndef WRITING_PROCESS_H
#define WRITING_PROCESS_H

#include "Process.h"

using namespace std;

class WritingProcess : public Process {
    public:
        WritingProcess(int id);
        virtual ~WritingProcess();

        bool execute() override;
        void printInfo() const override;
        string toString() const override;

    protected:

    private:
};

#endif // WRITING_PROCESS_H