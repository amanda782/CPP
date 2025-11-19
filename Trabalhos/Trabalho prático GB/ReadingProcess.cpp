#include "ReadingProcess.h"
#include "Sistema.h"
#include "ComputingProcess.h"
#include <fstream>  // p ler e escrever em arquivos (ifstream/ofstream)
#include <string>   
#include <iostream>

using namespace std; 

//referências devem ser "ligadas" (inicializadas) no exato momento em que são criadas. por isso sistema(s), e não sistema = s
ReadingProcess::ReadingProcess(int pid, Sistema& s):Processo(pid), sistema(s) {
	// o pid ja é tratado no construtor da classe mãe
}
ReadingProcess::~ReadingProcess() {}

void ReadingProcess::execute() {

	ifstream arquivoEntrada(nomeArquivo);

	if (!arquivoEntrada.is_open()) {
		cout << "AVISO: Arquivo " << nomeArquivo << " nao encontrado. Nenhuma expressao lida." << endl;
		return; 
	}

	string expressaoMat;
	int processosCriados = 0; 

	while (getline(arquivoEntrada, expressaoMat)) { // coloco expressao mat no arquivo
		if (expressaoMat.empty()) //pula linhas em branco e segue o baile
			continue;

		cout << "Lendo expressao: '" << expressaoMat << "'" << endl;
		
		int novoPid = sistema.getProximoPid(); // pega um pid unico p ele 

		Processo* p = new ComputingProcess(novoPid, expressaoMat); // crio um novo processo p de computing. passo o pid e a expressao por parametro.

		sistema.adicionarProcesso(p); // adiciono esse processo p na fila 

		processosCriados++; 
	}
	arquivoEntrada.close();
	cout << "Leitura concluida. " << processosCriados << " processos adicionados a fila." << endl;

	ofstream arquivoSaida(nomeArquivo, ofstream::trunc); // trunc é o que apaga totalmente o arquivo 
	if (arquivoSaida.is_open()) {
		arquivoSaida.close();
		cout << "Arquivo " << nomeArquivo << " foi limpo." << endl;
	}
	else {
		cout << "ERRO: Nao foi possivel limpar o arquivo " << nomeArquivo << "." << endl;
	}
}
void ReadingProcess::imprimeProcesso() {
	cout << "Tipo do processo: ReadingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}
void ReadingProcess::save(ofstream& arquivo) {
	// Formato: TIPO;PID;DADOS...
	arquivo << "READ;" << getPid() <<endl;
}

