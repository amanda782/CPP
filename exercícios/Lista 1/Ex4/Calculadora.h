#pragma once
#include <iostream>
#include <string>

using namespace std;

class Calculadora {
public:
	Calculadora() ;
	Calculadora(string c) ;
	~Calculadora() ;

	//metodos:
	float soma(float num1, float num2);
	float subtracao(float num1, float num2);
	float multiplicacao(float num1, float num2);
	float divisao(float num1, float num2);
	int eleva_ao_quadrado(int num1);
	int eleva_ao_cubo(int num1);
	void imprime_info();
	string get_cor();
	void set_cor(string cor_nova);
	float get_memoria();
	void set_memoria(float v);

	//atributos:
private:

	float memoria;
	string cor;

};



