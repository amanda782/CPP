#pragma once
#include <iostream>
#include "Processo.h"


class PrintingProcess:public Processo {
public:
	PrintingProcess();
	PrintingProcess(int pid);
	~PrintingProcess();
	void execute();
	void imprimeProcesso();
};
