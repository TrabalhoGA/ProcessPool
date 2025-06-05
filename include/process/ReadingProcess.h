#pragma once
#ifndef READING_PROCESS_H
#define READING_PROCESS_H

#include "Process.h"
#include "../queue/ProcessQueue.h"

using namespace std;
class ReadingProcess : public Process {
    public:
        ReadingProcess(int id, ProcessQueue* queue);
        virtual ~ReadingProcess();

        virtual bool execute() override;
        void printInfo() const override;
        string toString() const override;

    protected:

    private:
		ProcessQueue* processQueue;
};

#endif // READING_PROCESS_H