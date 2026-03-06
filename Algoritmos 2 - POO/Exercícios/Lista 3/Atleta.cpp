#include "Atleta.h"

Atleta::Atleta() {
	nome = " ";
	idade = 0;
}

Atleta::Atleta(string nome_atleta, int idade_atleta) {
	nome = nome_atleta;
	idade = idade_atleta;
}

Atleta::~Atleta(){}

void Atleta::imprime_info() {
	cout << "Nome do atleta: " << nome << endl;
	cout << "Idade do atleta: " << idade << endl;
}

string Atleta::get_nome() {
	return nome;
}

int Atleta::get_idade() {
	return idade;
}