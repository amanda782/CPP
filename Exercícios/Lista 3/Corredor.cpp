#include "Atleta.h"

#include "Competicao.h"
#include "Corredor.h"

Corredor::Corredor() {
	peso = 0;
}

Corredor::Corredor(string nome_corredor, int idade_corredor, float peso_corredor, Competicao comp_corredor) :Atleta( nome_corredor, idade_corredor) {
	peso = peso_corredor;
	competicao = comp_corredor;
}

Corredor::~Corredor(){}

void Corredor::imprime_competicao() {
	cout << "Nome da competicao: " << competicao.get_nome_comp() << endl;
	cout << "Data da competicao: ";
	competicao.imprime_data_comp();

}

void Corredor::imprime_info() {
	Atleta::imprime_info();
	cout << "Peso do corredor: " << peso << endl;
	imprime_competicao(); // quando estamos dentro da mesma classe, nao preciso citar o objeto e nem a classe pra chamar o metodo
}

float Corredor::get_peso() {
	return peso;
}

Competicao Corredor::get_comp() {
	return competicao;
}