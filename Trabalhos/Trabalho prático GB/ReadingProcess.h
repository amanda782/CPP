#pragma once
#include <iostream>
#include "Processo.h"
#include "FilaProcessos.h"
#include "Sistema.h"


class ReadingProcess :public Processo {
public:
	//ReadingProcess(); disse pra não colocar, pq o sistema precisa ser inicializado em outro lugar dai tb e fica bixado
	ReadingProcess(int pid, Sistema& s); // passo o sistema por parametro porque é por ele que eu vou pedir o pid e inserir na fila. 
	~ReadingProcess();
	void execute();
	void imprimeProcesso();
	// metodo pra ler e limpar o arquivo (talvez retornar uma string grande)
	// metodo pra instanciar os objetos e colocar na fila (talvez recebe essa string grande e vai separando)
	// metodo pra limpar o arquivo

private:
	Sistema& sistema;
	string nomeArquivo = "computation.txt";
};
