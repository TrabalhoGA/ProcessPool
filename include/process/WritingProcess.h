#pragma once
#ifndef WRITING_PROCESS_H
#define WRITING_PROCESS_H

#include "Process.h"
#include <fstream>


using namespace std;

class WritingProcess : public Process {
    public:
        WritingProcess(int id);
        virtual ~WritingProcess();

        bool execute() override;
        void printInfo() const override;
        string toString() const override;

        bool writeExpression(const string& expression);


    protected:

    private:
};

#endif // WRITING_PROCESS_H