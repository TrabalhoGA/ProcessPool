#include <locale>
#include "system/ProcessSystem.h"

int main() {
    // Configura o locale para português
    setlocale(LC_ALL, "pt-br.UTF-8");

    // Inicializa o sistema de processos
    ProcessSystem system;
    system.run();

    return 0;
}