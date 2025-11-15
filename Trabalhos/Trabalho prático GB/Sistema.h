#pragma once
#include <iostream>
#include "FilaProcessos.h"

using namespace std;

class Sistema {
public:
	Sistema(FilaProcessos* minhaFila);
	~Sistema();

	void executarProximo();
	void executarPorPid(int pid);
	void saveFila();
	void carregarFila();
	void iniciarSistema();

	void adicionarProcesso(Processo* p); // pega o processo que já foi criado e adiciona na fila. (readingprocess)
	int getProximoPid(); // garante que não tenham pid repetido. incrementa
	FilaProcessos& getFila(); // retorna a fila. usado no printing process. 


protected:
	FilaProcessos* fila;
	int pidCounter = 0;
};

