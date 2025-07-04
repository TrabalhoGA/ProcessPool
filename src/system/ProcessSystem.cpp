#include "system/ProcessSystem.h"
#include "process/WritingProcess.h"
#include "process/ReadingProcess.h"
#include "process/ComputingProcess.h"
#include "process/PrintingProcess.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

ProcessSystem::ProcessSystem() : taskManager(&processQueue), running(false) {
    // ctor
}

ProcessSystem::~ProcessSystem() {
    // dtor
}

void ProcessSystem::run() {
    running = true;
    while (running) {
        clearScreen();
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
    cout << "4. Exibir gerenciador de processos" << endl;
    cout << "5. Salvar fila em arquivo" << endl;
    cout << "6. Carregar fila do arquivo" << endl;
    cout << "7. Excluir processo específico" << endl;
    cout << "0. Sair" << endl;
    cout << "============================================" << endl;
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
    clearScreen();
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
            taskManager.show();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            removeProcess();
            break;
        case 0:
            exitSystem();
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
    }
}

void ProcessSystem::createProcess() {
    cout << "\n============== Criar Processo ==============" << endl;
    cout << "1. Processo de Cálculo" << endl;
    cout << "2. Processo de Gravação" << endl;
    cout << "3. Processo de Leitura" << endl;
    cout << "4. Processo de Impressão" << endl;
    cout << "0. Voltar ao menu principal" << endl;
    cout << "============================================" << endl;
    cout << "Escolha o tipo: ";
    
    int type = getMenuChoice();
    clearScreen();

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
        case 0:
            return;
        default:
            cout << "Tipo inválido!" << endl;
    }
}

void ProcessSystem::createComputingProcess() {
    cout << "\n========= Create Computing Process =========" << endl;
    cout << "Digite a expressão matemática do processo: " << endl;
    string expression;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
    getline(cin, expression);
    if (expression.empty()) {
        cout << "Expressão vazia! Processo não criado." << endl;
        return;
    }
	expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end()); // Remove espaços em branco para a classe Expression
    ComputingProcess* process = new ComputingProcess(-1, expression); // PID será atribuído pela fila
    int pid = processQueue.enqueue(process);
    cout << "============================================" << endl;
    cout << "Processo de cálculo criado e adicionado à fila com PID " << pid << ". Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ProcessSystem::createWritingProcess() {
	cout << "\n========= Create Writing Process =========" << endl;
    WritingProcess* process = new WritingProcess(-1); 
    int pid = processQueue.enqueue(process);
    cout << "\nProcesso de gravação criado e adicionado à fila com PID " << pid << ". Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::createReadingProcess() {
	cout << "\n========= Create Reading Process =========" << endl;
    ReadingProcess* process = new ReadingProcess(-1, &processQueue); 
    int pid = processQueue.enqueue(process);
    cout << "\nProcesso de leitura criado e adicionado à fila com PID " << pid << ". Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::createPrintingProcess() {
	cout << "\n========= Create Printing Process =========" << endl;
    PrintingProcess* process = new PrintingProcess(-1, &processQueue); 
    int pid = processQueue.enqueue(process);
    cout << "\nProcesso de impressão criado e adicionado à fila com PID " << pid << ". Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::executeNext() {
	cout << "\n=========== Execute Next Process ===========" << endl;
    if (processQueue.isEmpty()) {
        cout << "\nFila vazia! Nenhum processo para executar. Digite ENTER para continuar." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    cout << "\nExecutando próximo processo..." << endl;
    Process* process = processQueue.dequeue();
    if(process->execute()) {
        cout << "\nProcesso " << process->getPID() << " executado com sucesso! ";
    } 
    else {
        cout << "\nErro ao executar o processo " << process->getPID() << "! ";
    }
    cout << "Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    delete process;
}

void ProcessSystem::executeSpecific() {
	cout << "\n========= Execute Specific Process =========" << endl;
    if (processQueue.isEmpty()) {
        cout << "Fila vazia! Nenhum processo para executar. Digite ENTER para continuar." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    cout << "Digite o PID do processo: ";
    int pid = getMenuChoice();
    Process* process = processQueue.removeByPID(pid);
    if (process) {
        if(process->execute()){
            cout << "Processo " << pid << " executado com sucesso!" << endl;
        } 
        else {
            cout << "Erro ao executar o processo " << pid << "!" << endl;
        }
        delete process;
    } else {
        cout << "Processo com PID " << pid << " não encontrado!" << endl;
    }
    cout << "Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::removeProcess() {
	cout << "\n============ Remove Process ============" << endl;
    if (processQueue.isEmpty()) {
        cout << "Fila vazia! Nenhum processo para remover. Digite ENTER para continuar." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    cout << "Digite o PID do processo a ser removido: ";
    int pid = getMenuChoice();
    Process* process = processQueue.removeByPID(pid);
    if (process) {
        cout << "Processo com PID " << pid << " removido com sucesso!" << endl;
        delete process;
    } else {
        cout << "Processo com PID " << pid << " não encontrado!" << endl;
    }
    cout << "Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::saveToFile() {
	cout << "\n============ Save Queue to File ============" << endl;
    cout << "Digite o nome do arquivo: ";
    string filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> filename;
    if(processQueue.saveToFile(filename)){
        cout << "Fila salva no arquivo " << filename << endl;
    } else {
        cout << "Erro ao salvar a fila no arquivo " << filename << endl;
    }
    cout << "Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::loadFromFile() {
	cout << "\n=========== Load Queue from File ===========" << endl;
    cout << "Digite o nome do arquivo: ";
    string filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> filename;
    if(processQueue.loadFromFile(filename)) {
        cout << "Fila carregada do arquivo " << filename << endl;
    } else {
        cout << "Erro ao carregar a fila do arquivo " << filename << endl;
    }
    cout << "Digite ENTER para continuar." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ProcessSystem::exitSystem() {
    cout << "Encerrando sistema..." << endl;
    running = false;
}

void ProcessSystem::clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux / macOS
    #endif
}