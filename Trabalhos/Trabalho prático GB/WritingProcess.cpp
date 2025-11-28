#include "WritingProcess.h"



WritingProcess::WritingProcess():Processo() {
	
}

WritingProcess::WritingProcess(int pid,string expressao):Processo(pid) {
	PID = pid;
	calculo = expressao;
}

WritingProcess::~WritingProcess() {

}
void WritingProcess::imprimeProcesso() {
	cout << "Tipo do processo: WritingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
	cout << "Expressao escrita: " << calculo << endl;
}

void WritingProcess::execute() {
	//cria um objeto ofstream (fluxo de saída)
	// na criaçao desse objeto, passa dois argymentos: o nome do arquivo e a flag (modo de abertura)
	//ios::app significa usar APPEND, ou seja, nao sobrescrever o que ja temos.

	ofstream arquivo("computation.txt", ios::app); 

	if (!arquivo.is_open()) { // verifica se o arquivo abriu com sucesso
		cout << "Erro critico. Nao foi possivel abrir computation.txt para gravacao" << endl;
		return;
	}

	cout << "Executando processo de PID: " << getPid() << " || (WritingProcess)" << endl;
	arquivo << calculo << endl; // aqui ocorre a impressao no arquivo
	arquivo.close(); // fecha o arquivo
		
	cout << "Expressao gravada no arquivo." << endl; 
	
}
void WritingProcess::save(ofstream& arquivo) {
	arquivo << "WRITE;" << getPid()<<";"<<this->calculo << endl;
}


