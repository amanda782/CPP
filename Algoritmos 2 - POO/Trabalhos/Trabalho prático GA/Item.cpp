#include "Item.h"
#include <sstream>


Item::Item() {
	nome = "Item vazio";
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

char Item::get_tipo() {
	return tipo;
}

bool Item::get_combate() {
	return combate;
}
int Item::get_FA() {
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


stringstream ss; // cria uma string com FLUXO, onde incluímos vários pedaços
string Item::get_descricao() {
	ss << "Item: " << this->get_nome() << endl;

	if (this->isArma()) { // se for arma
		ss << "Tipo do item: Arma" << endl;
		ss << "Força de ataque: +" << this->forca_de_ataque << endl;
		ss<< "Dano: +" << this->dano << endl;
	}
	else if (this->isArmadura()) {
		ss << "Tipo do item: Armadura" << endl;
		ss << "Reduz Dano em: "  << this->dano <<endl;
	}

	ss << "Pode ser usado em combate: " << (this->get_combate() ? "Sim" : "Nao");
	return ss.str(); // entender melhor o this
}