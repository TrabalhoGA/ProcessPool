#pragma once
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "queue/ProcessQueue.h"
#include <string>
#include <vector>

using namespace std;

class TaskManager {
public:
    // Enum para ordenação
    enum SortType {
        SORT_BY_POSITION,
        SORT_BY_PID,
        SORT_BY_TYPE
    };

    // Enum para filtros
    enum FilterType {
        FILTER_ALL,
        FILTER_COMPUTING,
        FILTER_WRITING,
        FILTER_READING,
        FILTER_PRINTING
    };

    TaskManager(ProcessQueue* queue);
    virtual ~TaskManager();

    // Método principal do gerenciador de tarefas
    void show();

protected:

private:
    ProcessQueue* processQueue;
    SortType currentSortType;
    FilterType currentFilterType;
    string searchTerm;

    // Métodos de interface principal
    void displayProcessTable();
    void displayMenu();
    void handleMenuChoice(int choice);

    // Métodos de funcionalidades básicas (mantidas do sistema original)
    void executeSpecificProcess();
    void removeSpecificProcess();

    // Métodos de funcionalidades aprimoradas
    void showProcessStatistics();
    void filterProcesses();
    void sortProcesses();
    void searchProcesses();
    void showProcessDetails();
    void bulkOperations();
    void exportProcessList();
    
    // Métodos auxiliares
    vector<Process*> getFilteredAndSortedProcesses();
    bool matchesFilter(Process* process);
    bool matchesSearch(Process* process);
    void clearScreen();
    int getMenuChoice();
    string getProcessExpression(Process* process);
    string formatProcessType(const string& type);
    
    // Métodos de comparação para ordenação
    static bool compareByPID(Process* a, Process* b);
    static bool compareByType(Process* a, Process* b);
};

#endif // TASK_MANAGER_H