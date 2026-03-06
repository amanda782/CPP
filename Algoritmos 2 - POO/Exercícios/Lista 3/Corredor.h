#pragma once
#include <iostream>
#include <string>
#include "Atleta.h"
#include "Competicao.h"

using namespace std;

class Corredor :public Atleta {
public:
	Corredor();
	Corredor(string nome_corredor, int idade_corredor, float peso_corredor, Competicao comp_corredor);
	~Corredor();

	void imprime_competicao();
	void imprime_info();

	float get_peso();
	Competicao get_comp();

private:
	float peso;
	Competicao competicao;
};