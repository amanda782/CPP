#include "Produto.h"
#include "Laptops.h"

Laptops::Laptops() {
	marca_laptop = " ";
	tamanho_laptop = 0;
}

Laptops::Laptops(string nome, float preco, int codigo, string marca, float tamanho):Produto(nome, preco, codigo) {
	marca_laptop =marca;
	tamanho_laptop = tamanho;
}
Laptops::~Laptops(){}

string Laptops::get_marca() {
	return marca_laptop;
}
float Laptops::get_tamanho() {
	return tamanho_laptop;
}

void Laptops::imprime_info() {
	cout << "Nome do laptop: " << nome_produto << endl;
	cout << "Preco do laptop: " << preco_produto << endl;
	cout << "Codigo de barras do laptop: " << codigo_de_barras << endl;
	cout << "Marca do laptop: " << marca_laptop << endl;
	cout << "Tamanho do laptop: " << tamanho_laptop << endl << endl;
}

void Laptops::set_tamanho(float tamanho) {
	tamanho_laptop = tamanho;
	cout << endl << "Tamanho alterado com sucesso :)" << endl;
}
void Laptops::set_marca(string marca) {
	marca_laptop = marca;
	cout << endl << "Marca alterada com sucesso :)" << endl;
}