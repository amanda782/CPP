#include "Tablet.h"
#include "Produto.h"

Tablet::Tablet() {
	marca_tablet = " ";
	duracao_bateria = 0;

}
Tablet::Tablet(string nome, float preco, int codigo, string marca, float duracao):Produto( nome,  preco, codigo){
	marca_tablet = marca;
	duracao_bateria = duracao;
}
Tablet::~Tablet() {}

string Tablet::get_marca() {
	return marca_tablet;
}
float Tablet::get_duracao() {
	return duracao_bateria;
}

void Tablet::imprime_info() {
	cout << "Nome do tablet: " << nome_produto << endl;
	cout << "Preco do tablet: " << preco_produto << endl;
	cout << "Codigo de barras do tablet: " << codigo_de_barras << endl;
	cout << "Marca do tablet: " << marca_tablet << endl;
	cout << "Duracao da bateria: " << duracao_bateria << endl << endl;
}
void Tablet::set_bateria(float bateria) {
	duracao_bateria = bateria;
	cout << endl << "Bateria alterada com sucesso :)" << endl;
}
void Tablet::set_marca(string new_marca) {
	marca_tablet = new_marca;
	cout << endl << "Marca alterada com sucesso :)" << endl;
}