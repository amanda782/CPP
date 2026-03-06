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
	void save(ofstream& arquivo);

private:
	string calculoOriginal;
	CalculaExpressao calculo;
};