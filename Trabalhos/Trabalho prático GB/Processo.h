#pragma once
#include <iostream>

using namespace std;

class Processo {
public:
	Processo(); // construtor padrão
	Processo(int pid); // construtor principal
	~Processo(); // destrutor

	virtual void execute() = 0; // classe virtual PURA
	int getPid();
	virtual void imprimeProcesso() = 0;

protected:
	int PID;
};