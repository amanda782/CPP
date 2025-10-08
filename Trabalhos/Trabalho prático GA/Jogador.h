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
	Jogador(string name,int energia, int sorte, int habilidade, int provisoes);
	~Jogador();

	//metodos de acesso:
	int get_provisoes_atuais();
	vector<Item> get_inventario();
	int getTesouro();
	void imprime_inventario();


	//metodos de ataque:
	int calcular_FA();
	bool testar_sorte();

	//metodos de gerenciamento:
	bool usar_provisao();
	void adiciona_item(Item novo_item);
	void adiciona_provisao(int quantidade_provisoes);
	void equipar_item(int ponteiro_do_item); // recebe a posição do item no vetor inventário
	bool usar_sorte();
	int ampliar_dano(int dano_ampliar);
	int reduzir_dano(int dano_reduzir);

	void setProvisoes(int quantidade);
	void setTesouro(int quantidade);
	void limparInventario(); // Para esvaziar o inventario antes de carregar um novo

private:

	int provisoes_atual_jogador;
	int tesouro;
	vector<Item> inventario;
	Item arma_jogador;
	Item armadura_jogador;






};