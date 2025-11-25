#include "Sistema.h"
#include <string>
#include "WritingProcess.h"
#include "ComputingProcess.h"
#include "Processo.h"
#include "PrintingProcess.h"
#include "CalculaExpressao.h"
#include "ReadingProcess.h"
#include <fstream>
#include <sstream>
#include "FilaProcessos.h"

Sistema::Sistema(FilaProcessos* minhaFila) {
	fila = minhaFila;
	pidCounter = 1;
}
Sistema::~Sistema() { 

}
void Sistema::executarPorPid(int pid) {
	Processo* p = removerPorPid(pid);

	if (p != nullptr) {
		p->execute();
		delete p;     // limpar a memoria dps de cada execute
	}
	else {
		cout << "Processo nao encontrado na fila." << endl;
	}
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
	return pidAtual; // retorna o PID que deve ser usado
}
void Sistema::iniciarSistema() {
	cout << "Bem vindo ao POOL DE PROCESSOS" << endl;
	while (1) {
		cout << endl<<"O que voce deseja fazer: " << endl;
		cout << "1: Criar um processo de escrita" << endl;
		cout << "2: Criar um processo de leitura" << endl;
		cout << "3: Criar um processo de impressao" << endl;
		cout << "4: Executar o proximo processo da fila" << endl;
		cout << "5: Executar um processo especifico (por pid)" << endl;
		cout << "6: Salvar fila atual" << endl; 
		cout << "7: Carregar fila" << endl;     // (próximo passo)
		cout << "8: Sair" << endl << endl;

		int numero, pid_procurado;
		cin >> numero; // armazena a resposta do menu principal
		string expressao;

		switch (numero) {
		case 1: {
			cout << "Digite a expressao matematica a ser gravada: " << endl;
			cin.ignore(); // ignora o enter do ultimo cin
			getline(cin, expressao); // armazena a string do calculo em EXPRESSAO
			int PID = getProximoPid(); // pega o atual e ja incrementa para o proximo, nao precisamos nos preocupar com isso
			Processo* p = new WritingProcess(PID, expressao);
			fila->inserir(p);
			cout << "Processo de escrita (PID: " << PID << ") adicionado a fila. " << endl;
			break;
		}
		case 2: {
			int PID = getProximoPid();
			// 'this' é um ponteiro (Sistema*), mas o construtor espera
			// uma referência (Sistema&). O '*' faz o "dereference".
			Processo* p = new ReadingProcess(PID, *this);
			fila->inserir(p);
			cout << "Processo de leitura (PID: " << PID << ") adicionado a fila. " << endl;
			break;
		}
		case 3: {
			int PID = getProximoPid();
			Processo* p = new PrintingProcess(PID, this->fila);
			fila->inserir(p);
			cout << "Processo de impressao (PID: " << PID << ") adicionado a fila. " << endl;
			break;
		}
		case 4: {
			executarProximo();
			break;
		}
		case 5: {
			cout << "Digite o pid do processo que voce gostaria de executar: " << endl;
			cin >> pid_procurado;
			executarPorPid(pid_procurado);
			break;
		}
		case 6: { 
			saveFila();
			break;
		}
		case 7:
			carregarFila();
			break;
		case 8:
			return;
		default:
			cout << "Opcao invalida. Por favor, escolha um numero de 1 a 9." << endl;
			break; 
		}
	}
}

void Sistema::saveFila() {
	std::cout << "Salvando fila no arquivo 'fila_salva.txt'..." << std::endl;

	ofstream arquivo("fila_salva.txt"); // abre o arquivo, apagando o anterior

	if (!arquivo.is_open()) {
		std::cout << "ERRO: Nao foi possivel abrir o arquivo para salvar." << std::endl;
		return;
	}

	salvarFila(arquivo); // pede pra fila se salvar

	arquivo.close(); // fecha o arquivo
	cout << "Fila salva com sucesso." << std::endl;
}

void Sistema::carregarFila() {
	std::cout << "Carregando fila do 'fila_salva.txt'..." <<endl;

	std::ifstream arquivo("fila_salva.txt"); // abre o arquivo
	if (!arquivo.is_open()) {
		std::cout << "AVISO: 'fila_salva.txt' nao encontrado. Nao foi possivel inicializar a fila." << std::endl;
		return;
	}

	fila->limparFila(); // limpa a fila atual antes de comecar

	string linha, tipo, dados;
	int pid;
	int maxPid = 0; // para atualizar o pidCounter

	// lê o arquivo linha por linha
	while (getline(arquivo, linha)) {
		if (linha.empty()) 
			continue; // pula linhas em branco

		stringstream ss(linha);
		char delimitador; // para ignorar o ponto e vírgula

		getline(ss, tipo, ';'); // lê o TIPO
		ss >> pid >> delimitador;    // lê o PID e o ';'
		getline(ss, dados);     // lê o resto (a expressão, se houver)

		Processo* p = nullptr;

		// recria o Processo correto baseado no TIPO
		if (tipo == "COMPUTE") {
			p = new ComputingProcess(pid, dados); //
		}
		else if (tipo == "WRITE") {
			p = new WritingProcess(pid, dados);
		}
		else if (tipo == "READ") {
			p = new ReadingProcess(pid, *this); // 'this' é o Sistema
		}
		else if (tipo == "PRINT") {
			p = new PrintingProcess(pid, this->fila); //
		}

		if (p != nullptr) {
			fila->inserir(p); //
			if (pid > maxPid) {
				maxPid = pid; // guarda o maior PID encontrado
			}
		}
	}

	arquivo.close();

	// atualiza o pidCounter para evitar PIDs duplicados
	pidCounter = maxPid + 1; //

	cout << "Fila carregada com sucesso." <<endl;
	imprimirFila();  
}

void Sistema::executarProximo() {
	Processo* p = fila->removerProximo();
	if (p!= nullptr) {
		p->execute();
		delete p;
	}
	else {
		cout << "A fila esta vazia." << endl;
	}
}

void Sistema::salvarFila(ofstream& arquivo) {
	Node* atual = fila->topNode();
	while (atual != nullptr) {
		atual->processo->save(arquivo);
		atual = atual->proximo;
	}
}

Processo* Sistema::removerPorPid(int pid) {
	if (fila->topNode() == nullptr) // se for uma lista vazia
		return nullptr; // retorna nada

	else if (fila->topNode()->processo->getPid() == pid) { // nesse caso removemos o primeiro
		return fila->removerProximo();  // e ja temos metodo pra isso!!
	}

	else {
		int voltas = fila->size();;
		bool jaRemoveu = false;
		Processo* retornar = nullptr;
		for (int i = 0; i < voltas; i++) {
			//tira o primeiro
			Processo* removido = fila->removerProximo();

			//é o que queremos remover? e ainda não removemos?
			if (removido->getPid() == pid && !jaRemoveu) {
				// entao uardamos o valor e NÃO devolvemos para a fila (push)
				retornar = removido;
				jaRemoveu = true; // a partir daqui, nunca mais entra nessa verificacao/bloco de codigo
				// o item foi removido pois não demos push
			}
			else {
				//caso nao seja oq queremos, devolvemos para o final da fila
				fila->inserir(removido); //pusha o elemento que acabei de tirar do fim da fila
			}
		}

		return retornar;
	}

	return nullptr;

}

void Sistema::imprimirFila() {
	Node* atual = fila->topNode();
	if (atual == nullptr) {
		cout << "Fila vazia" << endl;
		return;
	}

	cout << "Fila do pool de processos: " << endl;
	while (atual != nullptr) {
		atual->processo->imprimeProcesso();
		cout << endl;
		atual = atual->proximo;
	}
}