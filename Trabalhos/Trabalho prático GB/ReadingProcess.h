#pragma once
#include <iostream>
#include "Processo.h"


class ReadingProcess :public Processo {
public:
	ReadingProcess();
	ReadingProcess(int pid);
	~ReadingProcess();
	void execute();
	void imprimeProcesso();

};
