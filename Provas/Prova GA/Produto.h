#pragma once
#include <iostream>
#include <string>

using namespace std;

class Produto {
public:
	Produto();
	Produto(string nome, float preco, int codigo);
	~Produto();

	string get_nome();
	float get_preco();
	int get_codigo();
	bool verifica_igualdade(Produto* x, Produto* y);
	void virtual imprime_info() = 0; // classe virtual PURA. nao pode existir produto produto
	void set_nome(string new_name);
	void set_preco(float novo_preco);
	void set_codigo(int new_codigo);


protected:
	string nome_produto;
	float preco_produto;
	int codigo_de_barras;
};
