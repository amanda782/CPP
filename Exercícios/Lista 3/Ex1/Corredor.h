#pragma once
#include <iostream>
#include <string>
#include "Atleta.h"
#include "Data.h"

using namespace std; 

class Corredor :public Atleta { //heran�a: NADADOR � um tipo de ATLETA. o nadador automaticamente ganha todos os atributos e m�todos p�blicos do atleta
public:
	Corredor(string nome, int idade, float peso, Competicao compt);
	~Corredor();

	//metodos:
	void imprime_competicao();
	void imprime_info();

private:
	float peso_corredor;
	Competicao competicao_corredor;

};



