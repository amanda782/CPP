#include "Cabeçalho.h"


Pessoa::Pessoa() {
	nome = "";
	idade = 0;
	altura = 0;
	irmaos = 0;
	endereco = "";
}
Pessoa::Pessoa(string n, int id, int alt, int irm, string end)
{
	nome = n; // o valor davariável n está sendo atribuído para o nome, que é um atributo do objeto pessoa.
	idade = id;
	altura = alt;
	irmaos = irm;
	endereco = end;
}

Pessoa::~Pessoa() {} //destrutor

void Pessoa::imprime_info() {
	cout << "Nome: " << nome << endl;
	cout << "Altura: " << altura << endl;
	cout << "Idade: " << idade << endl;
	cout << "Quantidade de irmãos: " << irmaos << endl;
	cout << "Endereco: " << endereco << endl; //imprime os atributos da classe
}

bool Pessoa::is_filho_unico() {
	return irmaos == 0; // se for falso retorna falso
	return irmaos == 0; // se for falso retorna falso
}