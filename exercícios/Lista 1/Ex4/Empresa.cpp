#include "FuncionarioCaixa.h"
#include "Calculadora.h"
#include "Empresa.h"

Empresa::Empresa() {
	nome = "";
}

Empresa::Empresa(string nom, FuncionarioCaixa x, FuncionarioCaixa y) {
	nome = nom;
	fulano = x;
	ciclano = y;
}

Empresa::~Empresa() {};

string Empresa::get_nome() {
	return nome;
}

void Empresa::set_nome(string novoNomee) {
		nome = novoNomee;
}

FuncionarioCaixa Empresa::get_funcionariox() {
	return fulano;
}

void Empresa::set_funcionariox(FuncionarioCaixa novoX) {
	fulano = novoX;
}

FuncionarioCaixa Empresa::get_funcionarioy() {
	return ciclano;
}

void Empresa::set_funcionarioy(FuncionarioCaixa novoY) {
	ciclano = novoY;
}

void Empresa::imprime_info() {
	cout << "Nome da empresa: " << nome << endl;
	cout << "Funcionário 1: " << fulano.get_nome() << endl;
	cout << "Funcionário 2: " << ciclano.get_nome() << endl;
}