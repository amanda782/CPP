#pragma once
#include <iostream>
#include "Processo.h"

using namespace std;

class WritingProcess :public Processo {
public:
	WritingProcess();
	WritingProcess(int pid);
	~WritingProcess();
	void execute();
	void imprimeProcesso();
};