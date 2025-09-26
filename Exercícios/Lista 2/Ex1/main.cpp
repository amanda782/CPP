#include "Equipe.h"
#include "Atleta.h"
#include "Esporte.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	Esporte e1("Vôlei", "Coletivo");
	Esporte e2("Ginastica", "Individual");

	e1.imprime_info();
	e2.imprime_info();

	Atleta a1("Amanda", 19);
	Equipe eq1("Amandinha", e1);
}