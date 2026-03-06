#include "FilaProcessos.h"

FilaProcessos::FilaProcessos() {
	head = nullptr;
	tail = nullptr;
	tamanho = 0;
}
FilaProcessos::~FilaProcessos() {
	limparFila();
}
FilaProcessos::FilaProcessos(Node* primeiro) {
	head = primeiro;
	tail = primeiro;
	tamanho = 0;
}
void FilaProcessos::inserir(Processo* proc) { // recebe o novo processo a ser colocado na fila (sempre no final)
	Node* novo = new Node; // cria um novo node, chamado NOVO
	novo->processo = proc;
	novo->proximo = nullptr;

	if (head != nullptr) { // se a fila nao estiver vazia
		tail->proximo = novo; // define o proximo do ultimo como o novo
		tail = novo; // define o novo como ultimo da fila
	}
	else { // se a fila estiver vazia
		head = novo; // o novo vai ser o inicio e o fim
		tail = novo;
	}
	tamanho++;
}
Processo* FilaProcessos::removerProximo() { // sempre remove o primeiro da fila e entrega pra quem chamou o metodo
	if (head == nullptr) // se a lista estiver vazia
		return nullptr; // avisa que nao tem nada pra remover

	Processo* primeiro = head->processo; // salva o primeiro PROCESSO da fila
	Node* nodeRemover = head; // salva o primeiro NODE da fila
	Node* proximo = head->proximo; // salva o proximo pra atualizar como primeiro da fila

	delete nodeRemover; // deleta o node do primeiro da fila
	head = proximo; // define o segundo como primeiro da fila

	if (head==nullptr) // se o que removemos fosse o unico na fila
		tail = nullptr; // definimos a lista como vazia
	tamanho--;
	return primeiro; // retornamos o que removemos para posterior processamento
}


bool FilaProcessos::find(int pid) {
	int voltas = this->tamanho;
	bool achou = false;
	for (int i = 0; i < voltas; i++) {
		//tira o primeiro
		Processo* removido = removerProximo();

		//é o que estamos procurando? e ainda não achamos?
		if (removido->getPid() == pid && !achou) {
			achou = true; // a partir daqui, nunca mais entra nessa verificacao/bloco de codigo

		}

		//sempre devolvemos pro final da fila
		inserir(removido); //pusha o elemento que acabei de tirar do fim da fila

	}
	return achou;
}


void FilaProcessos::limparFila() {
	Node* novo = head;
	Node* proximo = nullptr;

	while (novo != nullptr) {
		proximo = novo->proximo; //salva o proximo pra nao perdermos
		delete novo->processo; // deleta o PROCESSO 
		delete novo; // deleta o NODE 
		novo = proximo; // vai pro proximo da lista, se existir
	}
	//zeramos a lista por garantia
	head = nullptr;
	tail = nullptr;
	tamanho = 0;
}

int FilaProcessos::size() {
	return tamanho;
}

