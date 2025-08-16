#include "Pessoa.h"

Pessoa::Pessoa(string n, int id, int alt, int irm, string end)
{
	nome = n; // o valor davari�vel n est� sendo atribu�do para o nome, que � um atributo do objeto pessoa.
	idade = id;
	altura = alt;
	irmaos = irm;
	endereco = end;
}

Pessoa::~Pessoa() {} //destrutor

void Pessoa::imprime_info() {
	cout << n << endl << id << endl << alt << endl << irm << endl << end;
}

bool Pessoa::is_filho_unico() {
	if (irm > 0)
		return false;
	else
		return true;
}