#include <iostream>
#include "Nadador.h"
#include "Corredor.h"
#include "InformacoesAtleta.h"
#include "Data.h"
#include "Competicao.h"

int main() {
    // Criando os objetos
    Nadador nadador1("Cesar Cielo", 38, "50m Livre");

    Data dataCorrida(5, 9, 2025);
    Competicao maratona("Maratona de POA", dataCorrida);
    Corredor corredor1("Marilson dos Santos", 48, 62.5, maratona);

    // Criando nossa "caixa de ferramentas"
    InformacoesAtleta scanner;

    cout << "--- Testando Nadador ---" << endl;
    // Imprime tudo do nadador (nome, idade, categoria)
    scanner.imprime_informacoes_atleta(&nadador1); // passa como parametro o ATLETA que é o nadador 1
    // Usa o scanner para achar a informação exclusiva
    scanner.imprime_exclusivos_atleta(&nadador1);

    cout << "\n--- Testando Corredor ---" << endl;
    // Imprime tudo do corredor (nome, idade, peso, competicao)
    scanner.imprime_informacoes_atleta(&corredor1);
    // Usa o scanner para achar a informação exclusiva
    scanner.imprime_exclusivos_atleta(&corredor1);

    return 0;
}