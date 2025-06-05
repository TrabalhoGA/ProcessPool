#pragma once
#ifndef READING_PROCESS_H
#define READING_PROCESS_H

#include "Process.h"

using namespace std;
class ReadingProcess : public Process {
    public:
        ReadingProcess(int id);
        virtual ~ReadingProcess();

        bool execute() override;
        void printInfo() const override;
        string toString() const override;

    protected:

    private:
};

#endif // READING_PROCESS_H