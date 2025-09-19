#pragma once
#include <iostream>
#include <string>
#include "Entidade.h"
#include "Item.h"
#include <vector> 

using namespace std;

class Jogador: public Entidade {
public: // pra construir o jogador, precisamos definir a distribuição de pontos no MAIN
	Jogador();
	Jogador(int energia, int sorte, int habilidade, int provisoes);
	~Jogador();

	//metodos de acesso:
	int get_provisoes_atuais();

	//metodos de ataque:
	int calcular_FA();
	bool testar_sorte();

	//metodos de gerenciamento:
	bool usar_provisao();
	void adiciona_item(Item novo_item);
	void adiciona_provisao(int quantidade_provisoes);
	void equipar_item(int ponteiro_do_item); // recebe a posição do item no vetor inventário

	void setProvisoes(int quantidade);
	void setTesouro(int quantidade);
	void limparInventario(); // Para esvaziar o inventario antes de carregar um novo

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