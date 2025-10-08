#pragma once
#include <iostream>
#include <string>
#include "Data.h"
#include "Atleta.h"

using namespace std;

class Competicao {
public:
	Competicao();
	Competicao(string nome, Data date);
	~Competicao();

	//metodos:
	void imprime_data_comp();
	string get_nome();
	Data get_data();

private:
	string nome_competicao;
	Data data_competicao;
};