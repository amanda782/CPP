#include "FilaProcessos.h"
#include "ReadingProcess.h"
#include "ComputingProcess.h"
#include "Sistema.h"
#include <iostream>

using namespace std;

int main() {

	FilaProcessos minhaFila;
	Sistema meuSistema(&minhaFila);
	
	// SEMPRE INSERIR USANDO NEW. se não crasha no delete
	
	// sempre inserir PONTEIROS PARA PROCESSOS
	
	meuSistema.iniciarSistema();



	return 0;

	
}