#include "FuncionarioCaixa.h"
#include "Calculadora.h"


FuncionarioCaixa::FuncionarioCaixa() {
	nome = "";
	endereco = "";
};

FuncionarioCaixa::FuncionarioCaixa(string nom, string end, Calculadora cx) {
	nome = nom;
	endereco = end;
	c1 = cx;
};

FuncionarioCaixa::~FuncionarioCaixa() {};


string FuncionarioCaixa:: get_nome() {
	return nome;
}

// SET -> "altera" o valor do atributo
void FuncionarioCaixa::set_nome(string novoNome) {
	nome = novoNome;
}

void FuncionarioCaixa::set_endereco(string enderecoNovo) {
	endereco = enderecoNovo;
}

string FuncionarioCaixa::get_endereco() {
	return endereco;
}

void FuncionarioCaixa::set_calculadora(Calculadora novaCalculadora) {
	c1 = novaCalculadora;
}

Calculadora FuncionarioCaixa::get_calculadora() {
	return c1;
}
void FuncionarioCaixa::imprime_info() {
	cout << "O nome do funcionário é:  " << nome << endl;
	cout << "O endereço do funcionário é:  " << endereco << endl;
	cout << "A calculadora é de cor: " << c1.get_cor() << endl;
	cout << "Memória da calculadora: " << c1.get_memoria() << endl;
}

float FuncionarioCaixa::soma(float valor1, float valor2) {
	return c1.soma(valor1, valor2);
}

float FuncionarioCaixa::subtracao(float valor1, float valor2) {
	return c1.subtracao(valor1, valor2);
}

float FuncionarioCaixa::multiplicacao(float valor1, float valor2) {
	return c1.multiplicacao(valor1, valor2);
}

float FuncionarioCaixa::divisao(float valor1, float valor2) {
	return c1.divisao(valor1, valor2);
}

int FuncionarioCaixa::eleva_ao_quadrado(int valor1) {
	return c1.eleva_ao_quadrado(valor1);
}

int FuncionarioCaixa::eleva_ao_cubo(int valor1) {
	return c1.eleva_ao_cubo(valor1);
}


