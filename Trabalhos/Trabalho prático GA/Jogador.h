#pragma once
#include <iostream>
#include <string>
#include "Entidade.h"
#include "Item.h"
#include <vector> 

using namespace std;

class Jogador: public Entidade {
public:
	Jogador();
	Jogador(int energia, int sorte, int habilidade, int provisoes);
	~Jogador();

	//metodos de acesso:
	int get_provisoes_atuais();

	//metodos de ataque:
	int calcular_FA();
	bool testar_sorte();

	//metodos de gerenciamento:
	void usar_provisao();
	void adiciona_item(Item novo_item);
	void adiciona_provisao(int quantidade_provisoes);
	void equipar_item(Item equipar_item);

private:
	int energia_atual_jogador;
	int energia_maxima_jogador;
	int sorte_maxima_jogador;
	int sorte_atual_jogador;
	int habilidade_jogador;
	int provisoes_atual_jogador;
	int tesouro;
	vector<Item> inventario;
	Item arma_jogador;
	Item armadura_jogador;




};