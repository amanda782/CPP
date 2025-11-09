#include "WritingProcess.h"


WritingProcess::WritingProcess():Processo() {
	
}

WritingProcess::WritingProcess(int pid):Processo(pid) {
	PID = pid;
}

WritingProcess::~WritingProcess() {

}
void WritingProcess::execute() {
	//logica de ESCRITA no arquivo
}
void WritingProcess::imprimeProcesso() {
	cout << "Tipo do processo: WritingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}


