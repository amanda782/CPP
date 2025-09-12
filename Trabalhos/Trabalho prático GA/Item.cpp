#include "Item.h"

Item::Item() {
	nome = ' ' ;
	tipo = ' ';
	forca_de_ataque = 0;
	dano = 0;
}

Item::Item(string nome_do_item, char tipo_do_item, bool combate_do_item, int FA, int dano_do_item) {
	nome = nome_do_item;
	tipo = tipo_do_item;
	combate = combate_do_item;
	forca_de_ataque = FA;
	dano = dano_do_item;
}

Item::~Item(){}

string Item::get_nome() {
	return nome;
}

char Item::get_tipo_item() {
	return tipo;
}

bool Item::get_combate_item() {
	return combate;
}
int Item::get_FA_item() {
	return forca_de_ataque;
}
int Item::get_dano() {
	return dano;
}

bool Item::isArma(){
	if (tipo == 'w')
		return true;
	else
		return false;
}
bool Item::isArmadura() {
	if (tipo == 'a')
		return true;
	else
		return false;
}
void Item::get_descricao() {
	cout << "Item: " << get_nome() << endl;
	cout << "Tipo do item: " << get_tipo_item() << endl;
	cout << "Pode ser usado em combate: " get_combate_item() << endl;
}