#pragma once
#include <iostream>
#include <string>

using namespace std;

class Item {
public:
	Item();
	Item(string nome_do_item, char tipo_do_item, bool combate_do_item, int FA, int dano_do_item); // combate: pode ser usado em combate ou n�o. FA: for�a de ataque lida do .txt  Dano: diminui da energia ap�s um ataque.
	~Item();

	//metodos de acesso aos atributos:
	string get_nome(); // como o atributo � privado, aqui acessamos ele sem problemas
	char get_tipo();
	bool get_combate();
	int get_FA();
	int get_dano();

	//metodos utilit�rios:
	bool isArma();
	bool isArmadura();
	string get_descricao();

private:
	string nome;
	char tipo;
	bool combate;
	int forca_de_ataque;
	int dano;
};
