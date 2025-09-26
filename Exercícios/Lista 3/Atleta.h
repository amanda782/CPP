#pragma once
#include <iostream>
#include <string>

using namespace std;

class Atleta {
public: 
	Atleta();
	Atleta(string nome_atleta, int idade_atleta);
	~Atleta();

	virtual void imprime_info();
	string get_nome();
	int get_idade();


private:
	string nome;
	int idade;
};