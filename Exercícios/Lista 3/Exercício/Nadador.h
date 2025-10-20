#pragma once
#include <iostream>
#include <string>
#include "Data.h"
#include "Atleta.h"

using namespace std; 

class Nadador :public Atleta { //herança: NADADOR é um tipo de ATLETA. o nadador automaticamente ganha todos os atributos e métodos públicos do atleta
public:
	Nadador(string nome, int idade, string categoria); // preciso construir um atleta pra associar ao nadador

	//metodos:
	void imprime_info(); // Sobrescrevendo o método do Atleta
	string get_categoria(); // para poder acessar a categoria do esporte do atleta

private:
	string categoria; // aqui, adiciono só o que é novo (não tem no atleta)
};
