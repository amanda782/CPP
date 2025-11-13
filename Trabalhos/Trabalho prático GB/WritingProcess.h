#pragma once
#include <iostream>
#include "Processo.h"
#include "FilaProcessos.h"
#include <fstream>

using namespace std;

class WritingProcess :public Processo {
public:
	WritingProcess();
	WritingProcess(int pid,string calculo);
	~WritingProcess();
	void imprimeProcesso();
	void execute();
	void save(ofstream& arquivo);

protected:
	string calculo;
};