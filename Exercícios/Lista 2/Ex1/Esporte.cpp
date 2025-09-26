#include "Equipe.h"
#include "Atleta.h"
#include "Esporte.h"

Esporte::Esporte() {

};

Esporte::Esporte(string nom, string modalidad) {
	nome_do_esporte = nom;
	modalidade_do_esporte = modalidad;

};

Esporte::~Esporte() {

};

void Esporte::imprime_info() {
	cout << "Nome do esporte: " << nome_do_esporte << endl;
	cout << "Modalidade do esporte: " << modalidade_do_esporte << endl;

};

string Esporte::get_nome_esporte() {
	return nome_do_esporte;
};

string Esporte::get_modalidade() {
	return modalidade_do_esporte;
};