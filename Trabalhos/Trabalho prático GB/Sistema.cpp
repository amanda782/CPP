#include "Sistema.h"
#include <string>

Sistema::Sistema() {
	fila = new FilaProcessos(); 
	pidCounter = 1;
}
Sistema::~Sistema() { 

}
void Sistema::criarProcesso(int pid) {

}
void Sistema::executarPorPid(int pid) {

}
void Sistema::saveFila() {

}
void Sistema::carregarFila() {

}
void Sistema::adicionarProcesso(Processo* p) {
	fila->inserir(p);
	cout << "Processo (PID " << p->getPid() << ") adicionado a fila." << endl;
}
FilaProcessos& Sistema::getFila(){
	return *fila;
}
int Sistema::getProximoPid() {
	int pidAtual = pidCounter;
	pidCounter++; // incrementa para o próximo
	return pidAtual; // retorna o PID que acabou de ser usado
}
void Sistema::iniciarSistema() {
	cout << "Bem vindo ao POOL DE PROCESSOS" << endl;
	while (1) {
		cout << "O que voce deseja fazer: " << endl;
		cout << "1: Criar um processo de escrita (writting process) " << endl;
		cout << "2: Criar um processo de leitura (reading process)" << endl;
		cout << "3: Criar um processo de impressão (printing process)" << endl;
		cout << "4: Sair" << endl;

		int numero;
		cin >> numero; // armazena a resposta do menu principal
		string expressao;

		switch (numero) {
		case 1:
			cout << "Digite a expressao matematica a ser gravada: " << endl;
			cin.ignore(); // ignora o enter do ultimo cin
			getline(cin, expressao); // armazena a string do calculo em EXPRESSAO
			//Processo* p = new WritingProcess(pidCounter, expressao, fila);
			//aqui escreve no arquivo, falta metodos p isso
			pidCounter++;
			break;
		
		case 2:
			//chama metodo de leitura
			break;

		case 3:
			//chama metodo de impressao, só imprime na tela
			break;
		case 4:
			return;
		}
	}
}