#pragma once
#include <iostream>
#include <string>
#include "Produto.h"

using namespace std;

class Laptops :public Produto {
public:
	Laptops();
	Laptops(string nome, float preco, int codigo, string marca, float tamanho);
	~Laptops();

	string get_marca();
	float get_tamanho();
	void imprime_info();
	void set_tamanho(float tamanho);
	void set_marca(string marca);

private:
	string marca_laptop;
	float tamanho_laptop;
};