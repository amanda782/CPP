#pragma once
#include <iostream>
#include "Processo.h"
#include "CalculaExpressao.h"

using namespace std;

class ComputingProcess :public Processo {
public:
	ComputingProcess();
	ComputingProcess(int pid, string equacao);
	~ComputingProcess();
	void execute();
	void imprimeProcesso();
	// metodo que recebe a string e faz o calculo (retorna/imprime o resultado) "execute"

private:
	string calculoOriginal;
	CalculaExpressao calculo;
};