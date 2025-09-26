#pragma once
#include <iostream>
#include <string>
#include "Atleta.h"
#include "Competicao.h"

using namespace std;

class InformacoesAtleta {
public:
	InformacoesAtleta();
	~InformacoesAtleta();

	
	void imprime_exclusivos_atleta(Atleta* a); //recebe um ponteiro para um atleta


};