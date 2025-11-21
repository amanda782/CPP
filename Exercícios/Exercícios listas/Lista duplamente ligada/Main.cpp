#include <iostream>
#include <string>
#include "ListaOrdenada.h"

using namespace std;

int main() {
    cout << "=== TESTE 1: INTEIROS (DUPLAMENTE LIGADA) ===" << endl;
    ListaDuplamenteOrdenada<int> lista;

    cout << "inserindo baguncado: 50, 10, 100, 5" << endl;
    lista.insert(50);
    lista.insert(10);
    lista.insert(100); // vai pro tail
    lista.insert(5);   // vai pro head

    cout << "ordem normal: ";
    lista.print();
    // esperado: [5] <-> [10] <-> [50] <-> [100]

    cout << "ordem inversa (testando ponteiro anterior): ";
    lista.printInverso();
    // esperado: [100] <-> [50] <-> [10] <-> [5]


    cout << "\n=== TESTE 2: REMOCAO ===" << endl;
    cout << "removendo o 10 ." << endl;
    lista.remove(10);


    lista.print();
    // esperado: [10] <-> [50]

    cout << "\n=== TESTE 3: MERGE ===" << endl;
    ListaDuplamenteOrdenada<int> listaB;
    listaB.insert(20);
    listaB.insert(60);

    cout << "fazendo merge..." << endl;
    lista.merge(listaB);
    lista.print();
    // esperado: [10] <-> [20] <-> [50] <-> [60]

    return 0;
}