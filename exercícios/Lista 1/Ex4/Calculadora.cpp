#include "Calculadora.h"

Calculadora::Calculadora() { // classe::funcao
	memoria = 0;
	cor = " ";
}

Calculadora::Calculadora(string c) {
	cor = c;
}

Calculadora::~Calculadora() {};

float Calculadora::soma(float valor1, float valor2) {
	memoria = valor1 + valor2;
	return memoria;
}

float Calculadora::subtracao(float valor1, float valor2) {
	memoria = valor1 - valor2;
	return memoria;
}

float Calculadora::multiplicacao(float valor1, float valor2) {
	memoria = valor1 * valor2;
	return memoria;
}

float Calculadora::divisao(float valor1, float valor2) {
	memoria = valor1 / valor2;
	return memoria;
}

int Calculadora::eleva_ao_quadrado(int valor1) {
	memoria = valor1 * valor1;
	return memoria;
}

int Calculadora::eleva_ao_cubo(int valor1) {
	memoria = valor1 * valor1*valor1;
	return memoria;
}

void Calculadora::imprime_info() {
	cout << "A calculadora de cor: " << cor << endl;
	cout << "A memória da calculadora ficou: " << memoria << endl;
}

string Calculadora::get_cor() {
	return cor;
}

// SET -> "altera" o valor do atributo
void Calculadora::set_cor(string novaCor) {
	cor = novaCor;
}

void Calculadora::set_memoria(float valor) {
	memoria = valor;
}

float Calculadora::get_memoria() {
	return memoria;
}