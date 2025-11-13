#pragma once
#include <iostream>
#include "Processo.h"
#include "FilaProcessos.h"

using namespace std;

class PrintingProcess:public Processo {
public:
	PrintingProcess();
	PrintingProcess(int pid, FilaProcessos* fila);
	~PrintingProcess();
	void execute();
	void imprimeProcesso();
	void save(ofstream& arquivo);

private:
	FilaProcessos* fila;
};
