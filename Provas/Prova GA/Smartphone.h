#pragma once
#include <iostream>
#include <string>
#include "Produto.h"

using namespace std;

class Smartphone:public Produto {
public:
	Smartphone();
	Smartphone(string nome, float preco, int codigo, int modelo_smart, int capacidade);
	~Smartphone();

	int get_modelo();
	int get_capacidade();
	void imprime_info();
	void set_modelo(int modelo);
	void set_armazenamento(int capacidade);

private:
	int modelo;
	int capacidade_armazenamento;
};