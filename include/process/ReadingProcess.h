#pragma once
#ifndef READING_PROCESS_H
#define READING_PROCESS_H

#include "Process.h"

using namespace std;
class ReadingProcess : public Process {
    public:
        ReadingProcess();
        virtual ~ReadingProcess();

        bool execute() override;

    protected:

    private:
};

#endif // READING_PROCESS_H