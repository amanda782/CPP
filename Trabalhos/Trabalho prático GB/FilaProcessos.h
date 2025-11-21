#pragma once
#include <iostream>
#include "Processo.h"

using namespace std;

struct Node {
	Processo* processo; 
	Node* proximo;
};

class FilaProcessos {
public:
	FilaProcessos();
	FilaProcessos(Node* primeiro);
	~FilaProcessos();

	void inserir(Processo* proc); // add no final da fila
	Processo* removerProximo();
	Processo* removerPorPid(int pid);
	void imprimirFila();
	bool find(int pid);
	void salvarFila(ofstream& arquivo);
	void limparFila();
	int size();

protected:
	Node* head;
	Node* tail;
	int tamanho;
};
