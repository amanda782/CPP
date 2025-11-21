#include <iostream>
#include <string>
#include "Fila.h" 
using namespace std;

int main() {
    // Criando uma fila de Strings (nomes) com Prioridade Inteira
    Fila<string, int> filaDoBanco;

    cout << "=== TESTE 1: INSERCAO BASICA (PUSH) ===" << endl;
    // Vamos inserir fora de ordem para ver se ela arruma
    cout << "Inserindo: Joao (Prio 5)" << endl;
    filaDoBanco.push("Joao", 5);

    cout << "Inserindo: Maria (Prio 10) - DEVE FURAR FILA" << endl;
    filaDoBanco.push("Maria", 10);

    cout << "Inserindo: Pedro (Prio 1) - DEVE IR PRO FINAL" << endl;
    filaDoBanco.push("Pedro", 1);

    cout << "Inserindo: Ana (Prio 5) - DEVE FICAR ATRAS DO JOAO" << endl;
    filaDoBanco.push("Ana", 5);

    cout << "\n--- Estado da Fila ---" << endl;
    filaDoBanco.print();
    // Esperado: Maria(10) -> Joao(5) -> Ana(5) -> Pedro(1)

    cout << "\n=== TESTE 2: REMOCAO (POP) ===" << endl;
    cout << "Atendendo: " << filaDoBanco.pop() << endl; // Deve ser Maria
    cout << "Atendendo: " << filaDoBanco.pop() << endl; // Deve ser Joao

    cout << "\n--- Estado da Fila ---" << endl;
    filaDoBanco.print();
    // Esperado: Ana(5) -> Pedro(1)

    cout << "\n=== TESTE 3: BUSCA (FIND) ===" << endl;
    // Ana ainda está na fila?
    if (filaDoBanco.find("Ana"))
        cout << "Ana esta na fila? SIM (Correto)" << endl;
    else
        cout << "Ana esta na fila? NAO (Erro)" << endl;

    // Maria ainda está na fila?
    if (filaDoBanco.find("Maria"))
        cout << "Maria esta na fila? SIM (Erro)" << endl;
    else
        cout << "Maria esta na fila? NAO (Correto)" << endl;


    cout << "\n=== TESTE 4: REMOVER ESPECIFICO ===" << endl;
    // Vamos inserir mais gente para testar remover do meio
    filaDoBanco.push("Carlos", 2);
    filaDoBanco.push("Bia", 8);

    cout << "Fila antes de remover: ";
    filaDoBanco.print();
    // Esperado: Bia(8) -> Ana(5) -> Carlos(2) -> Pedro(1)

    cout << "Removendo 'Carlos' (que esta no meio)..." << endl;
    string removido = filaDoBanco.removerEspecifico("Carlos");
    cout << "Elemento removido: " << removido << endl;

    cout << "Fila apos remover: ";
    filaDoBanco.print();
    // Esperado: Bia(8) -> Ana(5) -> Pedro(1)

    cout << "\n=== TESTE 5: LIMPEZA ===" << endl;
    filaDoBanco.limpar();
    if (filaDoBanco.isEmpty()) {
        cout << "Fila limpa com sucesso!" << endl;
    }
    else {
        cout << "Erro ao limpar a fila." << endl;
    }

    return 0;
}