#include "Competicao.h"

Competicao::Competicao() {
	nome = " ";
}

Competicao::Competicao(string nome_comp, Data data) {
	nome = nome_comp;
	data_comp = data;
}

Competicao::~Competicao(){}

void Competicao::imprime_data_comp() {
	data_comp.imprime_data(); // sempre chama o metodo a partir do ATRIBUTO
}

string Competicao::get_nome_comp() {
	return nome; 
}

Data Competicao::get_data_comp() {
	return data_comp;
}