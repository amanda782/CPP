#include <string>
#include <iostream>
#include "Produto.h"
#include "Laptops.h"
#include "Smartphone.h"
#include "Tablet.h"
#pragma once

using namespace std;

class Loja {
public:
	Loja();
	Loja(string nome);
	~Loja();

	void imprime_produto(int codigo); // verifica se esta no estoque
	void adicionar_ao_estoque(Produto* product);
	void imprime_info_loja();
	void remover_do_estoque(int codigo);
	void valor_total();
	int verifica_produto(Produto* z);
	void aplicar_desconto(Produto* z, float porcentagem); 
	void editar_produto(Produto* x);
	void verificar_acima(float preco); // cria uma nova lista com todos produtos mais caros que o PRECO
	void realizar_venda(Produto* z);
	Produto* buscar_produto(int codigo);

private:
	string nome_loja;
	Produto* estoque[100];
	int tamanho_estoque;



};