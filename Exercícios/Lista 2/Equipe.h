#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Esporte.h"
#include "Atleta.h"

using namespace std;

class Equipe {
	Equipe();
	Equipe(string nome_equipe, Esporte esporte_praticado);
	~Equipe();

	//metodos:
	void adicionar_atleta(const Atleta& novo_atleta);
	void exibir_equipe();
	
private:
	string nome_da_equipe;
	Esporte esporte_da_equipe;
	Atleta vetorAtletas[30]; // vetor de 30 atletas
	int conta_atletas; //conta quantos atletas tem no time


};
