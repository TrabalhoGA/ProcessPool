#pragma once
#ifndef WRITING_PROCESS_H
#define WRITING_PROCESS_H

#include "Process.h"

using namespace std;

class WritingProcess : public Process {
    public:
        WritingProcess();
        virtual ~WritingProcess();

        bool execute() override;

    protected:

    private:
};

#endif // WRITING_PROCESS_H