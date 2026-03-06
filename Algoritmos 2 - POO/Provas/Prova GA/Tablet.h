#pragma once
#include <iostream>
#include <string>
#include "Produto.h"

using namespace std;

class Tablet :public Produto {
public:
	Tablet();
	Tablet(string nome, float preco, int codigo, string marca, float duracao);
	~Tablet();

	string get_marca();
	float get_duracao();
	void imprime_info();
	void set_bateria(float bateria);
	void set_marca(string new_marca);

private:
	string marca_tablet;
	float duracao_bateria;

};