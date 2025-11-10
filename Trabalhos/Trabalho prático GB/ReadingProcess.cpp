#include "ReadingProcess.h"


ReadingProcess::ReadingProcess():Processo() {

}
ReadingProcess::ReadingProcess(int pid, FilaProcessos* fila):Processo(pid) {
	PID = pid;
}
ReadingProcess::~ReadingProcess() {

}
void ReadingProcess::execute() {
	// logica de LEITURA do arquivo computation.txt
}
void ReadingProcess::imprimeProcesso() {
	cout << "Tipo do processo: ReadingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}

