#include "Produto.h"

Produto::Produto() {
	nome_produto = "teste";
	preco_produto = 0;
	codigo_de_barras = 0;
}

Produto::Produto(string nome, float preco, int codigo) {
	nome_produto = nome;
	preco_produto = preco;
	codigo_de_barras = codigo;
}

Produto::~Produto(){}

string Produto::get_nome() {
	return nome_produto;
}
float Produto::get_preco() {
	return preco_produto;
}
int Produto::get_codigo() {
	return codigo_de_barras;
}

bool Produto::verifica_igualdade(Produto* x, Produto* y) {
	if (x->get_codigo() == y->get_codigo()) //se os dois codigos forem iguais
		return true; // retorna true
	return false; // se nao forem iguais retorna false
}

void Produto::imprime_info() {
	cout << "Nome do produto: " << nome_produto << endl;
	cout << "Preco do produto: " << preco_produto << endl;
	cout << "Codigo de barras do produto: " << codigo_de_barras << endl;
}

void Produto::set_nome(string new_name) {
	nome_produto = new_name;
	cout << endl << "Nome alterado com sucesso :)" << endl;
}
void Produto::set_preco(float novo_preco) {
	preco_produto=novo_preco;
	cout << endl << "Preco alterado com sucesso :)" << endl;
}
void Produto::set_codigo(int new_codigo) {
	codigo_de_barras = new_codigo;
}