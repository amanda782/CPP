#pragma once
#include <iostream>
#include "Processo.h"
#include "FilaProcessos.h"
#include "Sistema.h"


class ReadingProcess :public Processo {
public:
	
	ReadingProcess(int pid, Sistema& s); // passo o sistema por parametro porque é por ele que eu vou pedir o pid e inserir na fila. 
	~ReadingProcess();
	void execute();
	void imprimeProcesso();
	void save(ofstream& arquivo);

private:
	Sistema& sistema;
	string nomeArquivo = "computation.txt";
};
