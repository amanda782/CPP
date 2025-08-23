#pragma once
#include <iostream>
#include <string>
#include "Calculadora.h"
#include "FuncionarioCaixa.h"

using namespace std;

class Empresa {
public:
	Empresa();
	Empresa(string nom, FuncionarioCaixa x, FuncionarioCaixa y);
	~Empresa();

	//metodos
	string get_nome();
	void set_nome(string nom);
	FuncionarioCaixa get_funcionariox();
	void set_funcionariox(FuncionarioCaixa x);
	FuncionarioCaixa get_funcionarioy();
	void set_funcionarioy(FuncionarioCaixa y);
	void imprime_info();

private: 
	string nome;
	FuncionarioCaixa fulano;
	FuncionarioCaixa ciclano;

};