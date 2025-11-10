#include "ComputingProcess.h"

ComputingProcess::ComputingProcess():Processo() {

}
ComputingProcess::ComputingProcess(int pid, string equacao):Processo(pid) {
	PID = pid;
	calculo = equacao;
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