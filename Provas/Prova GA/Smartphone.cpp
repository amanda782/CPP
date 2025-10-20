#include "Smartphone.h"
#include "Produto.h"

Smartphone::Smartphone() {
	modelo = 0;
	capacidade_armazenamento = 0;
}

Smartphone::Smartphone(string nome, float preco, int codigo, int modelo_smart, int capacidade):Produto(nome, preco, codigo) {
	modelo = modelo_smart;
	capacidade_armazenamento = capacidade;
}

Smartphone::~Smartphone(){}

int Smartphone::get_modelo() {
	return modelo;
}
int Smartphone::get_capacidade() {
	return capacidade_armazenamento;
}

void Smartphone::imprime_info() {
	cout << "Nome do smartphone: " << nome_produto << endl;
	cout << "Preco do smartphone: " << preco_produto << endl;
	cout << "Codigo de barras do smartphone: " << codigo_de_barras << endl;
	cout << "Modelo do smartphone: " << modelo << endl;
	cout << "Capacidade de armazenamento do smartphone: " << capacidade_armazenamento << endl << endl;
}

void Smartphone::set_modelo(int modelo) {
	this->modelo = modelo;
	cout << endl << "Modelo alterado com sucesso :)" << endl;
}
void Smartphone::set_armazenamento(int capacidade) {
	capacidade_armazenamento = capacidade;
	cout << endl << "Armazenamento alterado com sucesso :)" << endl;
}

