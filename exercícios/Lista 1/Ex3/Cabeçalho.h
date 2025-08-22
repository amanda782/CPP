#pragma once
#include <iostream>
#include<string>

using namespace std;

class Biblioteca {

public:
	Biblioteca();
	Biblioteca(string t, string au, int a);
	~Biblioteca();

	//metodos:
	void imprime_infos();
	void idade_do_livro();

	//atributos
private:
	string título;
	string autor;
	int ano;

};

