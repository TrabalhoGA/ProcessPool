#include "system/TaskManager.h"
#include "process/ComputingProcess.h"
#include "process/WritingProcess.h"
#include "process/ReadingProcess.h"
#include "process/PrintingProcess.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <fstream>

using namespace std;

TaskManager::TaskManager(ProcessQueue* queue) 
    : processQueue(queue), currentSortType(SORT_BY_POSITION), 
      currentFilterType(FILTER_ALL), searchTerm("") {
    // Constructor
}

TaskManager::~TaskManager() {
    // Destructor
}

void TaskManager::show() {
    int choice = -1;
    while (choice != 0) {
        clearScreen();
        displayProcessTable();
        displayMenu();
        choice = getMenuChoice();
        handleMenuChoice(choice);
    }
}

void TaskManager::displayProcessTable() {
    cout << "\n+======================== GERENCIADOR DE TAREFAS ========================+" << endl;
    
    // Exibir informações de filtro/ordenação atual
    cout << "| Filtro: " << setw(15);
    switch(currentFilterType) {
        case FILTER_ALL: cout << "Todos"; break;
        case FILTER_COMPUTING: cout << "Cálculo"; break;
        case FILTER_WRITING: cout << "Gravação"; break;
        case FILTER_READING: cout << "Leitura"; break;
        case FILTER_PRINTING: cout << "Impressão"; break;
    }
    cout << " | Ordenação: " << setw(10);
    switch(currentSortType) {
        case SORT_BY_POSITION: cout << "Posição"; break;
        case SORT_BY_PID: cout << "PID"; break;
        case SORT_BY_TYPE: cout << "Tipo"; break;
    }
    if (!searchTerm.empty()) {
        cout << " | Busca: " << searchTerm;
    }
    cout << " |" << endl;
    
    cout << "+----------+------+------------------------+----------------------------+" << endl;
    cout << "| Posição  | PID  | Tipo de Processo       | Expressão/Detalhes         |" << endl;
    cout << "+----------+------+------------------------+----------------------------+" << endl;
    
    vector<Process*> processes = getFilteredAndSortedProcesses();
    
    if (processes.empty()) {
        cout << "|          |      | Nenhum processo        |                            |" << endl;
        cout << "|          |      | encontrado!            |                            |" << endl;
    } else {
        for (size_t i = 0; i < processes.size(); ++i) {
            Process* process = processes[i];
            if (process) {
                string expression = getProcessExpression(process);
                string formattedType = formatProcessType(process->getType());
                
                cout << "| " << setw(8) << i + 1 << " | "
                     << setw(4) << process->getPID() << " | "
                     << setw(22) << formattedType << " | "
                     << setw(26) << expression << " |" << endl;
            }
        }
    }
    cout << "+----------+------+------------------------+----------------------------+" << endl;
}

void TaskManager::displayMenu() {
    cout << "| OPERAÇÕES DISPONÍVEIS:                                                  |" << endl;
    cout << "+----------------------------------------------------------------------+" << endl;
    
    if (!processQueue->isEmpty()) {
        cout << "| 1. Executar processo específico    | 2. Excluir processo específico |" << endl;
        cout << "| 3. Detalhes do processo             | 4. Operações em lote           |" << endl;
    }
    
    cout << "| 5. Estatísticas                     | 6. Filtrar processos           |" << endl;
    cout << "| 7. Ordenar processos                | 8. Buscar processos            |" << endl;
    cout << "| 9. Exportar lista                   | 0. Voltar ao menu principal    |" << endl;
    cout << "+----------------------------------------------------------------------+" << endl;
    cout << "Digite uma opção: ";
}

void TaskManager::handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            if (!processQueue->isEmpty()) executeSpecificProcess();
            break;
        case 2:
            if (!processQueue->isEmpty()) removeSpecificProcess();
            break;
        case 3:
            if (!processQueue->isEmpty()) showProcessDetails();
            break;
        case 4:
            if (!processQueue->isEmpty()) bulkOperations();
            break;
        case 5:
            showProcessStatistics();
            break;
        case 6:
            filterProcesses();
            break;
        case 7:
            sortProcesses();
            break;
        case 8:
            searchProcesses();
            break;
        case 9:
            exportProcessList();
            break;
        case 0:
            return;
        default:
            cout << "Opção inválida! Pressione ENTER para continuar." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
    }
}

void TaskManager::executeSpecificProcess() {
    cout << "\n========= EXECUTAR PROCESSO ESPECÍFICO =========" << endl;
    cout << "Digite o PID do processo: ";
    int pid = getMenuChoice();
    
    Process* process = processQueue->removeByPID(pid);
    if (process) {
        cout << "Executando processo " << pid << "..." << endl;
        if (process->execute()) {
            cout << "Processo " << pid << " executado com sucesso!" << endl;
        } else {
            cout << "Erro ao executar o processo " << pid << "!" << endl;
        }
        delete process;
    } else {
        cout << "Processo com PID " << pid << " não encontrado!" << endl;
    }
    
    cout << "Pressione ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void TaskManager::removeSpecificProcess() {
    cout << "\n========= EXCLUIR PROCESSO ESPECÍFICO =========" << endl;
    cout << "Digite o PID do processo: ";
    int pid = getMenuChoice();
    
    Process* process = processQueue->removeByPID(pid);
    if (process) {
        cout << "Processo com PID " << pid << " removido com sucesso!" << endl;
        delete process;
    } else {
        cout << "Processo com PID " << pid << " não encontrado!" << endl;
    }
    
    cout << "Pressione ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void TaskManager::showProcessStatistics() {
    cout << "\n================== ESTATÍSTICAS ==================" << endl;
    
    int totalProcesses = processQueue->getSize();
    int computingCount = 0, writingCount = 0, readingCount = 0, printingCount = 0;
    
    for (int i = 0; i < totalProcesses; ++i) {
        Process* process = processQueue->getProcessAt(i);
        if (process) {
            string type = process->getType();
            if (type == "ComputingProcess") computingCount++;
            else if (type == "WritingProcess") writingCount++;
            else if (type == "ReadingProcess") readingCount++;
            else if (type == "PrintingProcess") printingCount++;
        }
    }
    
    cout << "Total de processos: " << totalProcesses << endl;
    cout << "Processos de Cálculo: " << computingCount << endl;
    cout << "Processos de Gravação: " << writingCount << endl;
    cout << "Processos de Leitura: " << readingCount << endl;
    cout << "Processos de Impressão: " << printingCount << endl;
    
    if (totalProcesses > 0) {
        cout << "\nPercentuais:" << endl;
        cout << "Cálculo: " << fixed << setprecision(1) << (computingCount * 100.0 / totalProcesses) << "%" << endl;
        cout << "Gravação: " << (writingCount * 100.0 / totalProcesses) << "%" << endl;
        cout << "Leitura: " << (readingCount * 100.0 / totalProcesses) << "%" << endl;
        cout << "Impressão: " << (printingCount * 100.0 / totalProcesses) << "%" << endl;
    }
    
    cout << "\nPressione ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void TaskManager::filterProcesses() {
    cout << "\n============= FILTRAR PROCESSOS =============" << endl;
    cout << "1. Todos os processos" << endl;
    cout << "2. Apenas processos de Cálculo" << endl;
    cout << "3. Apenas processos de Gravação" << endl;
    cout << "4. Apenas processos de Leitura" << endl;
    cout << "5. Apenas processos de Impressão" << endl;
    cout << "Escolha o filtro: ";
    
    int filterChoice = getMenuChoice();
    switch (filterChoice) {
        case 1: currentFilterType = FILTER_ALL; break;
        case 2: currentFilterType = FILTER_COMPUTING; break;
        case 3: currentFilterType = FILTER_WRITING; break;
        case 4: currentFilterType = FILTER_READING; break;
        case 5: currentFilterType = FILTER_PRINTING; break;
        default:
            cout << "Filtro inválido!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
    }
    
    cout << "Filtro aplicado com sucesso!" << endl;
}

void TaskManager::sortProcesses() {
    cout << "\n============= ORDENAR PROCESSOS =============" << endl;
    cout << "1. Por posição na fila (padrão)" << endl;
    cout << "2. Por PID" << endl;
    cout << "3. Por tipo de processo" << endl;
    cout << "Escolha a ordenação: ";
    
    int sortChoice = getMenuChoice();
    switch (sortChoice) {
        case 1: currentSortType = SORT_BY_POSITION; break;
        case 2: currentSortType = SORT_BY_PID; break;
        case 3: currentSortType = SORT_BY_TYPE; break;
        default:
            cout << "Ordenação inválida!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
    }
    
    cout << "Ordenação aplicada com sucesso!" << endl;
}

void TaskManager::searchProcesses() {
    cout << "\n============= BUSCAR PROCESSOS =============" << endl;
    cout << "Digite o termo de busca (PID ou expressão): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchTerm);
    
    cout << "Busca por '" << searchTerm << "' aplicada com sucesso!" << endl;
    cout << "Pressione ENTER para continuar." << endl;
    cin.get();
}

void TaskManager::showProcessDetails() {
    cout << "\n========= DETALHES DO PROCESSO =========" << endl;
    cout << "Digite o PID do processo: ";
    int pid = getMenuChoice();
    
    Process* process = processQueue->findByPID(pid);
    if (process) {
        cout << "\n=== DETALHES DO PROCESSO ===" << endl;
        cout << "PID: " << process->getPID() << endl;
        cout << "Tipo: " << formatProcessType(process->getType()) << endl;
        
        // Detalhes específicos por tipo
        if (process->getType() == "ComputingProcess") {
            ComputingProcess* compProcess = static_cast<ComputingProcess*>(process);
            cout << "Expressão: " << compProcess->getExpression() << endl;
        } else if (process->getType() == "WritingProcess") {
            cout << "Descrição: Processo para gravar dados em arquivo" << endl;
        } else if (process->getType() == "ReadingProcess") {
            cout << "Descrição: Processo para ler dados de arquivo" << endl;
        } else if (process->getType() == "PrintingProcess") {
            cout << "Descrição: Processo para imprimir a fila de processos" << endl;
        }
        
        cout << "Status: Aguardando execução" << endl;
    } else {
        cout << "Processo com PID " << pid << " não encontrado!" << endl;
    }
    
    cout << "\nPressione ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void TaskManager::bulkOperations() {
    cout << "\n========= OPERAÇÕES EM LOTE =========" << endl;
    cout << "1. Executar todos os processos" << endl;
    cout << "2. Excluir todos os processos" << endl;
    cout << "3. Executar todos os processos filtrados" << endl;
    cout << "4. Excluir todos os processos filtrados" << endl;
    cout << "Escolha a operação: ";
    
    int bulkChoice = getMenuChoice();
    
    switch (bulkChoice) {
        case 1: {
            cout << "Executando todos os processos..." << endl;
            int executed = 0;
            while (!processQueue->isEmpty()) {
                Process* process = processQueue->dequeue();
                if (process->execute()) {
                    executed++;
                }
                delete process;
            }
            cout << executed << " processos executados com sucesso!" << endl;
            break;
        }
        case 2: {
            cout << "Excluindo todos os processos..." << endl;
            int deleted = processQueue->getSize();
            processQueue->clear();
            cout << deleted << " processos excluídos!" << endl;
            break;
        }
        case 3: {
            cout << "Executando processos filtrados..." << endl;
            vector<Process*> toExecute = getFilteredAndSortedProcesses();
            int executed = 0;
            for (Process* process : toExecute) {
                Process* removed = processQueue->removeByPID(process->getPID());
                if (removed && removed->execute()) {
                    executed++;
                }
                delete removed;
            }
            cout << executed << " processos executados com sucesso!" << endl;
            break;
        }
        case 4: {
            cout << "Excluindo processos filtrados..." << endl;
            vector<Process*> toDelete = getFilteredAndSortedProcesses();
            int deleted = 0;
            for (Process* process : toDelete) {
                Process* removed = processQueue->removeByPID(process->getPID());
                if (removed) {
                    deleted++;
                    delete removed;
                }
            }
            cout << deleted << " processos excluídos!" << endl;
            break;
        }
        default:
            cout << "Operação inválida!" << endl;
    }
    
    cout << "Pressione ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void TaskManager::exportProcessList() {
    cout << "\n========= EXPORTAR LISTA =========" << endl;
    cout << "Digite o nome do arquivo: ";
    string filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> filename;
    
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Erro ao criar arquivo!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    
    file << "=== LISTA DE PROCESSOS ===" << endl;
    file << "Total de processos: " << processQueue->getSize() << endl << endl;
    
    vector<Process*> processes = getFilteredAndSortedProcesses();
    for (size_t i = 0; i < processes.size(); ++i) {
        Process* process = processes[i];
        if (process) {
            file << "Posição: " << (i + 1) << endl;
            file << "PID: " << process->getPID() << endl;
            file << "Tipo: " << formatProcessType(process->getType()) << endl;
            file << "Expressão/Detalhes: " << getProcessExpression(process) << endl;
            file << "---" << endl;
        }
    }
    
    file.close();
    cout << "Lista exportada para " << filename << " com sucesso!" << endl;
    cout << "Pressione ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

vector<Process*> TaskManager::getFilteredAndSortedProcesses() {
    vector<Process*> processes;
    
    // Coletar todos os processos
    for (int i = 0; i < processQueue->getSize(); ++i) {
        Process* process = processQueue->getProcessAt(i);
        if (process && matchesFilter(process) && matchesSearch(process)) {
            processes.push_back(process);
        }
    }
    
    // Aplicar ordenação
    switch (currentSortType) {
        case SORT_BY_PID:
            sort(processes.begin(), processes.end(), compareByPID);
            break;
        case SORT_BY_TYPE:
            sort(processes.begin(), processes.end(), compareByType);
            break;
        case SORT_BY_POSITION:
        default:
            // Manter ordem original da fila
            break;
    }
    
    return processes;
}

bool TaskManager::matchesFilter(Process* process) {
    if (currentFilterType == FILTER_ALL) return true;
    
    string type = process->getType();
    switch (currentFilterType) {
        case FILTER_COMPUTING: return type == "ComputingProcess";
        case FILTER_WRITING: return type == "WritingProcess";
        case FILTER_READING: return type == "ReadingProcess";
        case FILTER_PRINTING: return type == "PrintingProcess";
        default: return true;
    }
}

bool TaskManager::matchesSearch(Process* process) {
    if (searchTerm.empty()) return true;
    
    // Buscar por PID
    if (to_string(process->getPID()).find(searchTerm) != string::npos) {
        return true;
    }
    
    // Buscar por expressão (apenas para ComputingProcess)
    if (process->getType() == "ComputingProcess") {
        ComputingProcess* compProcess = static_cast<ComputingProcess*>(process);
        string expression = compProcess->getExpression();
        if (expression.find(searchTerm) != string::npos) {
            return true;
        }
    }
    
    return false;
}

void TaskManager::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int TaskManager::getMenuChoice() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Entrada inválida! Digite um número: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

string TaskManager::getProcessExpression(Process* process) {
    if (process->getType() == "ComputingProcess") {
        try {
            return static_cast<ComputingProcess*>(process)->getExpression();
        } catch (const std::bad_cast& e) {
            return "N/A";
        }
    } else {
        return "N/A";
    }
}

string TaskManager::formatProcessType(const string& type) {
    if (type == "ComputingProcess") return "Cálculo";
    if (type == "WritingProcess") return "Gravação";
    if (type == "ReadingProcess") return "Leitura";
    if (type == "PrintingProcess") return "Impressão";
    return type;
}

bool TaskManager::compareByPID(Process* a, Process* b) {
    return a->getPID() < b->getPID();
}

bool TaskManager::compareByType(Process* a, Process* b) {
    return a->getType() < b->getType();
}