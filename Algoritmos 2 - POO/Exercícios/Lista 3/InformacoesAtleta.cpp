#include "Atleta.h"
#include "Corredor.h"
#include "Nadador.h"
#include "InformacoesAtleta.h"

InformacoesAtleta::InformacoesAtleta() {

}

InformacoesAtleta::~InformacoesAtleta(){}


void InformacoesAtleta::imprime_exclusivos_atleta(Atleta* atleta) {
	if (Nadador* n = dynamic_cast<Nadador*>(atleta)) {
		cout << "É um nadador, e sua categoria é: " << n->get_categoria();
	}
	else if (Corredor* c = dynamic_cast<Corredor*>(atleta)) {
		cout << "É um corredor, e o peso deste corredor é: " << c->get_peso();
	}
	else {
		cout << "Apenas um atleta.";
	}
}