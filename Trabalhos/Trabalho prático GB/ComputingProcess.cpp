#include "ComputingProcess.h"

ComputingProcess::ComputingProcess():Processo() {

}
ComputingProcess::ComputingProcess(int pid):Processo(pid) {
	PID = pid;
}
ComputingProcess::~ComputingProcess() {

}

void ComputingProcess:: execute() {
	//logica do calculo.
}

void ComputingProcess::imprimeProcesso() {
	cout << "Tipo do processo: ComputingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}