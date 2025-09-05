#pragma once
#include <iostream>
#include <string>
#include "Data.h"
#include "Atleta.h"

using namespace std; 

class Nadador :public Atleta { //heran�a: NADADOR � um tipo de ATLETA. o nadador automaticamente ganha todos os atributos e m�todos p�blicos do atleta
public:
	Nadador(string nome, int idade, string categoria); // preciso construir um atleta pra associar ao nadador

	//metodos:
	void imprime_info(); // Sobrescrevendo o m�todo do Atleta
	string get_categoria(); // para poder acessar a categoria do esporte do atleta

private:
	string categoria; // aqui, adiciono s� o que � novo (n�o tem no atleta)
};
