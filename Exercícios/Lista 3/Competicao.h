#pragma once
#include <iostream>
#include <string>
#include "Data.h"

using namespace std;

class Competicao {
public:
	Competicao();
	Competicao(string nome_comp, Data data);
	~Competicao();

	void imprime_data_comp();
	string get_nome_comp();
	Data get_data_comp();

private:
	string nome;
	Data data_comp;

};