#pragma once
#include <iostream>

using namespace std;

class Pessoa {
public:
	Pessoa(); //sempre precisa existir o construtor universal único
	Pessoa(string nome, int idade, int altura, int irmaos, string endereco);
	~Pessoa();

	//metodos
	void imprime_info();
	bool is_filho_unico(int irmaos);

	//atributos
private:
	string nome;
	int idade;
	int altura;
	int irmaos;
	string endereco;
};
