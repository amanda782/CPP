#pragma once
#include <iostream>
#include <string>
#include "Atleta.h"

using namespace std;

class Nadador :public Atleta {
public:
	Nadador();
	Nadador(string nome_atleta, int idade_atleta, string categoria_nadador);
	~Nadador();

	void imprime_info();
	string get_categoria();

private:
	string categoria;
};