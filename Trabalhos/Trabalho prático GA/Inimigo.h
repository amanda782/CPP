#pragma once
#include<iostream>
#include<string>
#include"Entidade.h"
#include"Item.h"
using namespace std;

class Inimigo: public Entidade {

public: 
	Inimigo();
	Inimigo(string name, int ability, int energy, int luck, int tesouroDrop, int provisoesDrop, Item itemDrop);
	~Inimigo();

	int getTesouroDeixado();
	int getProvisoesDeixadas();
	Item getItemDeixado();


private:
	int tesouroDeixado;
	int provisoesDeixadas;
	Item itemDeixado;
};