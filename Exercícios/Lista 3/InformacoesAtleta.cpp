#include "Atleta.h"
#include "Corredor.h"
#include "Nadador.h"
#include "InformacoesAtleta.h"

InformacoesAtleta::InformacoesAtleta() {

}

InformacoesAtleta::~InformacoesAtleta(){}


void InformacoesAtleta::imprime_exclusivos_atleta(Atleta* atleta) {
	if (Nadador* n = dynamic_cast<Nadador*>(atleta)) {
		cout << "� um nadador, e sua categoria �: " << n->get_categoria();
	}
	else if (Corredor* c = dynamic_cast<Corredor*>(atleta)) {
		cout << "� um corredor, e o peso deste corredor �: " << c->get_peso();
	}
	else {
		cout << "Apenas um atleta.";
	}
}