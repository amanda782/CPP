#include "Equipe.h"
#include "Atleta.h"
#include "Esporte.h"

Atleta::Atleta() {

};

Atleta::Atleta(string nome, int idade) {
	nome_do_atleta = nome;
	idade_do_atleta = idade;
};

Atleta::~Atleta() {};

void Atleta::imprime_info() {
	cout << "Nome do atleta: " << nome_do_atleta << endl;
	cout << "Idade do atleta: " << idade_do_atleta << endl;

};

string Atleta::get_nome_atleta() {
	return nome_do_atleta;
};

int Atleta::get_idade_atleta() {
	return idade_do_atleta;
};
