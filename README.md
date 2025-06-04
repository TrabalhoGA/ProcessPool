# Estrutura de Diretórios
```
ProcessPool/
├── app/
│   └── main.cpp
├── include/
│   ├── process/
│   │   ├── Process.h
│   │   ├── ComputingProcess.h
│   │   ├── WritingProcess.h
│   │   ├── ReadingProcess.h
│   │   └── PrintingProcess.h
│   ├── expression/
│   │   └── Expression.h
│   ├── queue/
│   │   ├── ProcessQueue.h
│   │   └── ProcessNode.h
│   └── system/
│       └── ProcessSystem.h
├── src/
│   ├── process/
│   │   ├── Process.cpp
│   │   ├── ComputingProcess.cpp
│   │   ├── WritingProcess.cpp
│   │   ├── ReadingProcess.cpp
│   │   └── PrintingProcess.cpp
│   ├── expression/
│   │   └── Expression.cpp
│   ├── queue/
│   │   ├── ProcessQueue.cpp
│   │   └── ProcessNode.cpp
│   └── system/
│       └── ProcessSystem.cpp
├── data/
│   └── computation.txt
└── Makefile
```
# Relacionamento das Classes
## Hierarquia de Herança
- Process (classe abstrata base)
  - ComputingProcess (herda de Process)
  - WritingProcess (herda de Process)
  - ReadingProcess (herda de Process)
  - PrintingProcess (herda de Process)

## Classes de Apoio
- Expression: classe para representar e calcular expressões aritméticas
- ProcessQueue: implementação da fila dinâmica para gerenciar os processos
- ProcessNode: representa cada elemento da fila dinâmica de processos (nó da fila)
- ProcessSystem: classe principal que gerencia todo o sistema (menu, operações)

## Relacionamentos de Composição/Agregação
- ProcessSystem tem uma ProcessQueue
- ComputingProcess tem uma Expression
- ReadingProcess tem referência para ProcessQueue (para adicionar processos lidos)
- PrintingProcess tem referência para ProcessQueue (para imprimir a fila)
- ProcessQueue é composta por vários ProcessNode (cada nó representa um processo na fila)

## Responsabilidades por Arquivo

### Process.h/.cpp:
- Classe base abstrata com pid e método virtual execute()

### ComputingProcess.h/.cpp:
- Herda de Process, contém Expression, implementa execute() para calcular
  
### WritingProcess.h/.cpp:
- Herda de Process, implementa execute() para gravar no arquivo

### ReadingProcess.h/.cpp:
- Herda de Process, implementa execute() para ler arquivo e criar ComputingProcess

### PrintingProcess.h/.cpp:
- Herda de Process, implementa execute() para imprimir fila

### Expression.h/.cpp:
- Gerencia operandos, operador e cálculo da expressão

### ProcessQueue.h/.cpp:
- Implementa fila dinâmica com operações de inserir, remover, buscar por PID

### ProcessNode.h/.cpp:
- Define a estrutura do nó da fila dinâmica de processos. Cada nó armazena um ponteiro para um objeto Process e um ponteiro para o próximo nó da fila. Usado internamente pela ProcessQueue.

### ProcessSystem.h/.cpp:
- Gerencia menu, criação de processos, execução, salvamento/carregamento
