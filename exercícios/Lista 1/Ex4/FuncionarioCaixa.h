#pragma once
#include <iostream>
#include <string>
#include "Calculadora.h"

using namespace std;

class FuncionarioCaixa {
public:
	FuncionarioCaixa();
	FuncionarioCaixa(string nom, string end, Calculadora cx);
	~FuncionarioCaixa();

	//metodos:
	string get_nome();
	void set_nome(string nom);
	string get_endereco();
	void set_endereco(string end);
	Calculadora get_calculadora();
	void set_calculadora(Calculadora calc);
	float soma(float num1, float num2);
	float subtracao(float num1, float num2);
	float multiplicacao(float num1, float num2);
	float divisao(float num1, float num2);
	int eleva_ao_quadrado(int num1);
	int eleva_ao_cubo(int num1);
	void imprime_info();

private:
	string nome;
	string endereco;
	Calculadora c1;
};
