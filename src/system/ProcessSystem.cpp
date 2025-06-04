#include "system/ProcessSystem.h"
#include <iostream>
#include <limits>

using namespace std;

ProcessSystem::ProcessSystem() : running(false) {
    // ctor
}

ProcessSystem::~ProcessSystem() {
    // dtor
}

void ProcessSystem::run() {
    running = true;
    while (running) {
        showMenu();
        int choice = getMenuChoice();
        handleMenuChoice(choice);
    }
}

void ProcessSystem::showMenu() {
    cout << "\n=================== MENU ===================" << endl;
    cout << "1. Criar processo" << endl;
    cout << "2. Executar próximo processo" << endl;
    cout << "3. Executar processo específico" << endl;
    cout << "4. Imprimir fila de processos" << endl;
    cout << "5. Salvar fila em arquivo" << endl;
    cout << "6. Carregar fila do arquivo" << endl;
    cout << "0. Sair" << endl;
    cout << "=============================================" << endl;
    cout << "Escolha uma opção: ";
}

int ProcessSystem::getMenuChoice() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Entrada inválida! Digite um número: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

void ProcessSystem::handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            createProcess();
            break;
        case 2:
            executeNext();
            break;
        case 3:
            executeSpecific();
            break;
        case 4:
            printProcessQueue();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 0:
            exitSystem();
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
    }
}

void ProcessSystem::createProcess() {
    cout << "\n=== Criar Processo ===" << endl;
    cout << "1. Processo de Cálculo" << endl;
    cout << "2. Processo de Gravação" << endl;
    cout << "3. Processo de Leitura" << endl;
    cout << "4. Processo de Impressão" << endl;
    cout << "Escolha o tipo: ";
    
    int type = getMenuChoice();
    
    switch (type) {
        case 1:
            createComputingProcess();
            break;
        case 2:
            createWritingProcess();
            break;
        case 3:
            createReadingProcess();
            break;
        case 4:
            createPrintingProcess();
            break;
        default:
            cout << "Tipo inválido!" << endl;
    }
}

void ProcessSystem::createComputingProcess() {
    cout << "Método createComputingProcess não implementado ainda." << endl;
}

void ProcessSystem::createWritingProcess() {
    cout << "Método createWritingProcess não implementado ainda." << endl;
}

void ProcessSystem::createReadingProcess() {
    cout << "Método createReadingProcess não implementado ainda." << endl;
}

void ProcessSystem::createPrintingProcess() {
    cout << "Método createPrintingProcess não implementado ainda." << endl;
}

void ProcessSystem::executeNext() {
    if (processQueue.isEmpty()) {
        cout << "Fila vazia! Nenhum processo para executar." << endl;
        return;
    }
    
    cout << "\n=== Executando Próximo Processo ===" << endl;
    
    Process* process = processQueue.dequeue();
    if(process->execute()) {
        cout << "Processo " << process->getPID() << " executado com sucesso!" << endl;

    } else {
        cout << "Erro ao executar o processo " << process->getPID() << "!" << endl;
    }

    delete process;

    cout << "Processo executado e removido da fila!" << endl;
}

void ProcessSystem::executeSpecific() {
    if (processQueue.isEmpty()) {
        cout << "Fila vazia! Nenhum processo para executar." << endl;
        return;
    }
    
    cout << "Digite o PID do processo: ";
    int pid = getMenuChoice();
    
    Process* process = processQueue.findByPID(pid);
     if (process) {
         if(process->execute()){
                cout << "Processo " << pid << " executado com sucesso!" << endl;
            } else {
                cout << "Erro ao executar o processo " << pid << "!" << endl;
         }
         delete process;
         cout << "Processo " << pid << " executado!" << endl;
     } else {
         cout << "Processo com PID " << pid << " não encontrado!" << endl;
     }
    
    cout << "Buscando e executando processo PID " << pid << "..." << endl;
}

void ProcessSystem::printProcessQueue() {
    cout << "\n=== Fila de Processos ===" << endl;
    
    if (processQueue.isEmpty()) {
        cout << "Fila vazia!" << endl;
        return;
    }
    
    processQueue.printQueue();
}

void ProcessSystem::saveToFile() {
    cout << "Digite o nome do arquivo: ";
    string filename;
    cin >> filename;
    
    if(processQueue.saveToFile(filename)){
        cout << "Fila salva no arquivo " << filename << endl;
    } else {
        cout << "Erro ao salvar a fila no arquivo " << filename << endl;
    }
}

void ProcessSystem::loadFromFile() {
    cout << "Digite o nome do arquivo: ";
    string filename;
    cin >> filename;
    
    if(processQueue.loadFromFile(filename)) {
        cout << "Fila carregada do arquivo " << filename << endl;
    } else {
        cout << "Erro ao carregar a fila do arquivo " << filename << endl;
    }
}

void ProcessSystem::exitSystem() {
    cout << "Encerrando sistema..." << endl;
    running = false;
}