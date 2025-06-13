#pragma once
#ifndef PROCESS_SYSTEM_H
#define PROCESS_SYSTEM_H

#include "queue/ProcessQueue.h"
#include <string>

using namespace std;

class ProcessSystem {
    public:
        ProcessSystem();
        virtual ~ProcessSystem();

        void run();

    protected:

    private:
        ProcessQueue processQueue;
        bool running;

        // Menu
        void showMenu();
        int getMenuChoice();
        void handleMenuChoice(int choice);

        // Métodos do menu
        void createProcess();
        void executeNext();
        void executeSpecific();
        void removeProcess();
        void saveToFile();
        void loadFromFile();
        void exitSystem();

        // Métodos auxiliares
        void createComputingProcess();
        void createWritingProcess();
        void createReadingProcess();
        void createPrintingProcess();
        void showTaskManager();

        // Outros
        void clearScreen();
};

#endif // PROCESS_SYSTEM_H
