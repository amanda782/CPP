#pragma once
#include <iostream>
#include <string>

using namespace std;

class Esporte {
public:
	Esporte();
	Esporte(string nome, string modalidade);
	~Esporte();

	//metodos::
	void imprime_info();
	string get_nome_esporte();
	string get_modalidade();


private:
	string nome_do_esporte;
	string modalidade_do_esporte;

};