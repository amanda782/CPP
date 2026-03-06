#include "Nadador.h"
#include "Atleta.h"

Nadador::Nadador() {
	categoria = " ";
}
// no construtor, tambem criamos uma classe mae, unindo por :
Nadador::Nadador(string nome_atleta, int idade_atleta, string categoria_nadador):Atleta(nome_atleta, idade_atleta) {
	categoria = categoria_nadador; // aqui dentro só vai os atributos da classe filha pq ja chamamos o construtor de atleta

}

Nadador::~Nadador(){}

void Nadador::imprime_info() {
	Atleta::imprime_info();
	cout << "Categoria do nadador: " << categoria << endl;
}

string Nadador::get_categoria() {
	return categoria;
}
