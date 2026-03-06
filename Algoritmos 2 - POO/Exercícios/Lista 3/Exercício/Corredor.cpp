#include "Nadador.h"
#include "Competicao.h"
#include "Data.h"
#include "Atleta.h"
#include "Corredor.h"

Corredor::Corredor(string nome, int idade, float peso, Competicao competicao):Atleta(nome, idade) { // na classe mae nao vai string e int, é uma passagem por paramet
	peso_corredor = peso;
	competicao_corredor = competicao;

}

Corredor::~Corredor() {

}

void Corredor::imprime_competicao() {
	competicao_corredor.imprime_comp();
}

void Corredor::imprime_info() {
	Atleta::imprime_info();
	cout << "Peso do corredor: " << peso_corredor << endl;


}