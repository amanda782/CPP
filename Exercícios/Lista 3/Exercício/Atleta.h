#pragma once
#include <iostream>
#include <string>

using namespace std;

class Atleta {
public:
	Atleta();
	Atleta(string nome, int idade);
	virtual ~Atleta();

	//metodos:
	virtual void imprime_info();
	string get_nome_atleta();
	int get_idade_atleta();


private:
	string nome_do_atleta;
	int idade_do_atleta;

};
