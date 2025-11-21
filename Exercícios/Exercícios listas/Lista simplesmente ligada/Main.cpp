#include <iostream>
#include <string>
#include "ListaOrdenada.h" // O arquivo que criamos antes

using namespace std;

int main() {
    // ==========================================
    // TESTE 1: NÚMEROS INTEIROS E ORDENAÇÃO
    // ==========================================
    cout << "=== TESTE 1: INTEIROS ===" << endl;
    ListaOrdenada<int> listaNumeros;

    cout << "Inserindo: 50, 10, 30, 5, 100 (Fora de ordem)..." << endl;
    listaNumeros.insert(50);
    listaNumeros.insert(10);
    listaNumeros.insert(30);
    listaNumeros.insert(5);
    listaNumeros.insert(100);

    cout << "Resultado (Deve estar crescente): ";
    listaNumeros.print();
    // Esperado: [5] -> [10] -> [30] -> [50] -> [100] -> NULL


    // ==========================================
    // TESTE 2: REMOÇÃO E BUSCA
    // ==========================================
    cout << "\n=== TESTE 2: REMOCAO E BUSCA ===" << endl;

    // Teste Find
    if (listaNumeros.find(30)) cout << "Achou 30? SIM (Correto)" << endl;
    else cout << "Achou 30? NAO (Erro)" << endl;

    if (listaNumeros.find(99)) cout << "Achou 99? SIM (Erro)" << endl;
    else cout << "Achou 99? NAO (Correto)" << endl;

    // Teste Remove
    cout << "Removendo 5 (Inicio)..." << endl;
    listaNumeros.remove(5);

    cout << "Removendo 100 (Fim)..." << endl;
    listaNumeros.remove(100);

    cout << "Removendo 30 (Meio)..." << endl;
    listaNumeros.remove(30);

    cout << "Lista apos remocoes: ";
    listaNumeros.print();
    // Esperado: [10] -> [50] -> NULL


    // ==========================================
    // TESTE 3: MERGE (MISTURAR LISTAS)
    // ==========================================
    cout << "\n=== TESTE 3: MERGE (MISTURAR) ===" << endl;
    ListaOrdenada<int> listaA;
    listaA.insert(2);
    listaA.insert(4);
    listaA.insert(6);

    ListaOrdenada<int> listaB;
    listaB.insert(1);
    listaB.insert(3);
    listaB.insert(5);

    cout << "Lista A (Pares): "; listaA.print();
    cout << "Lista B (Impares): "; listaB.print();

    cout << "-> Fazendo Merge da B dentro da A..." << endl;
    listaA.merge(listaB);

    cout << "Lista A Final: "; listaA.print();
    // Esperado: [1] -> [2] -> [3] -> [4] -> [5] -> [6] -> NULL


    // ==========================================
    // TESTE 4: STRINGS (ORDEM ALFABÉTICA)
    // ==========================================
    cout << "\n=== TESTE 4: STRINGS ===" << endl;
    ListaOrdenada<string> listaNomes;

    cout << "Inserindo: Zebra, Amanda, Bruno..." << endl;
    listaNomes.insert("Zebra");
    listaNomes.insert("Amanda");
    listaNomes.insert("Bruno");

    cout << "Lista de Nomes: ";
    listaNomes.print();
    // Esperado: [Amanda] -> [Bruno] -> [Zebra] -> NULL

    return 0;
}