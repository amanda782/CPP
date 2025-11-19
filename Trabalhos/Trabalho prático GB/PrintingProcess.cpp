#include "PrintingProcess.h"
#include "Processo.h"
#include "Sistema.h"

PrintingProcess::PrintingProcess(int pid, FilaProcessos* fila):Processo(pid) {
	PID = pid;
	this->fila = fila;
}
PrintingProcess::PrintingProcess():Processo() {
	fila = nullptr;
}
PrintingProcess::~PrintingProcess() {

}
void PrintingProcess::execute() {
	cout << "Executando processo de pid: " << PID << " (PrintingProcess)" << endl;
	fila->imprimirFila();
}
void PrintingProcess::imprimeProcesso() {
	cout << "Tipo do processo: PrintingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}
void PrintingProcess::save(ofstream& arquivo) {
	arquivo << "PRINT;" << getPid() <<endl;
}

