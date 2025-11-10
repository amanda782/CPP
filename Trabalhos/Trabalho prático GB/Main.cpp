#include "FilaProcessos.h"
#include "ReadingProcess.h"
#include "ComputingProcess.h"

#include <iostream>

using namespace std;

int main() {
	FilaProcessos minhaFila;
	Processo* p1 = new ReadingProcess(10); // SEMPRE INSERIR USANDO NEW. se não crasha no delete
	Processo* p2 = new ComputingProcess(11);

	minhaFila.inserir(p1); // sempre inserir PONTEIROS PARA PROCESSOS
	minhaFila.inserir(p2);

	minhaFila.removerPorPid(11);

	minhaFila.imprimirFila();


	
}