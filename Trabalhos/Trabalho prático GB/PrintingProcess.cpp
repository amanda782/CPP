#include "PrintingProcess.h"
#include "Processo.h"

PrintingProcess::PrintingProcess(int pid):Processo(pid) {
	PID = pid;
}
PrintingProcess::PrintingProcess():Processo() {
	
}
PrintingProcess::~PrintingProcess() {

}
void PrintingProcess::execute() {
	// logica de impressão da fila do pool de processos
}
void PrintingProcess::imprimeProcesso() {
	cout << "Tipo do processo: PrintingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}

