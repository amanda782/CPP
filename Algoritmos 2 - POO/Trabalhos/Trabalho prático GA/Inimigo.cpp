#include"Entidade.h"
#include"Inimigo.h"

Inimigo::Inimigo(){
	tesouroDeixado = 0;
	provisoesDeixadas = 0;

}

Inimigo::Inimigo(string name, int ability, int energy, int luck, int tesouroDrop, int provisoesDrop, Item itemDrop):Entidade(name,ability,energy,luck) {
	tesouroDeixado = tesouroDrop;
	provisoesDeixadas = provisoesDrop;
	itemDeixado = itemDrop;
	
}

Inimigo::~Inimigo() {}

int Inimigo::getTesouroDeixado() {
	return tesouroDeixado;
}

int Inimigo::getProvisoesDeixadas() {
	return provisoesDeixadas;
}

Item Inimigo::getItemDeixado() {
	return itemDeixado;
}


void Inimigo::setTesouroDeixado(int quantidade) {
	tesouroDeixado = quantidade;
}

void Inimigo::setProvisoesDeixadas(int quantidade) {
	provisoesDeixadas = quantidade;
}

void Inimigo::setItemDeixado(Item novoItem) {
	itemDeixado = novoItem;
}