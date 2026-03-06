#include <string>
#include <iostream>
#include "Corredor.h"
#include "Nadador.h"
#include "Competicao.h"
#include "Data.h"
#include "InformacoesAtleta.h"

using namespace std;

int main() {
	Nadador n1("Amanda", 19, "livre");

	//criando o ponteiro:
	Atleta* a = &n1;
	InformacoesAtleta impressora; //preciso instanciar um objeto para poder utilizar os metodos
	impressora.imprime_exclusivos_atleta(a); // passa somente o nome da variavel ptr
	return 0;

}