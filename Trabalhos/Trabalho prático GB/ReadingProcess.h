#pragma once
#include <iostream>
#include "Processo.h"
#include "FilaProcessos.h"


class ReadingProcess :public Processo {
public:
	ReadingProcess();
	ReadingProcess(int pid, FilaProcessos* fila);
	~ReadingProcess();
	void execute();
	void imprimeProcesso();
	// metodo pra ler e limpar o arquivo (talvez retornar uma string grande)
	// metodo pra instanciar os objetos e colocar na fila (talvez recebe essa string grande e vai separando)
	// metodo pra limpar o arquivo
};
