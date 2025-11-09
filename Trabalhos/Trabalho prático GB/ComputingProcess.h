#pragma once
#include <iostream>
#include "Processo.h"

using namespace std;

class ComputingProcess :public Processo {
public:
	ComputingProcess();
	ComputingProcess(int pid);
	~ComputingProcess();
	void execute();
	void imprimeProcesso();

private:

};