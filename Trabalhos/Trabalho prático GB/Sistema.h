#pragma once
#include <iostream>
#include "FilaProcessos.h"
#include "WritingProcess.h"
#include "ComputingProcess.h"
#include "ReadingProcess.h"
#include "Processo.h"
#include "PrintingProcess.h"

class Sistema {
public:
	Sistema();
	~Sistema();

	void criarProcesso(int pid);
	void executarProximo();
	void executarPorPid(int pid);
	void saveFila();
	void carregarFila();
	void iniciarSistema();


protected:
	FilaProcessos* fila;
	int pidCounter = 0;
};

