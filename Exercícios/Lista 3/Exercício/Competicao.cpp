#include "Competicao.h"
#include "Data.h"
#include "Atleta.h"


Competicao::Competicao() {

}

Competicao::Competicao(string nome, Data date) {
	nome_competicao = nome;
	data_competicao = date;
}

Competicao::~Competicao() {}

void Competicao::imprime_comp() {
	cout << "Data da competicao: ";
	data_competicao.imprime_data();
	cout << "Nome da competição: " << get_nome() << endl;

}

string Competicao::get_nome() {
	return nome_competicao;
}

Data Competicao::get_data() {
	return data_competicao;
}



