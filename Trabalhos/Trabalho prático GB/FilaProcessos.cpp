#include "FilaProcessos.h"

FilaProcessos::FilaProcessos() {
	head = nullptr;
	tail = nullptr;
}
FilaProcessos::~FilaProcessos() {
	limparFila();
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

	return primeiro; // retornamos o que removemos para posterior processamento
}
Processo* FilaProcessos::removerPorPid(int pid) {
	if (head == nullptr) // se for uma lista vazia
		return nullptr; // retorna nada

	if (head->processo->getPid() == pid) // nesse caso removemos o primeiro
		return removerProximo();  // e ja temos metodo pra isso!!

	Node* atual = head->proximo;
	Node* anterior = head; // aqui ja verificamos e nao encontramos
	
	while (atual!=nullptr) { // vamos percorrer a lista toda
		if (atual->processo->getPid() == pid) { // procurando pelo pid solicitado. caso encontrado:
			anterior->proximo = atual -> proximo; // religando a lista, pulando o atual
			if (tail == atual) // se o que removemos era o ultimo
				tail = anterior; // fazemos o anterior a ele ser o ultimo

			Processo* encontrado = atual->processo; // guardamos o processo com o pid encontrado
			delete atual; // deletamos o node da lista
			return encontrado; //retorna o encontrado
		}
		// se nao encontramos, os dois dao um passo:
		atual = atual->proximo;
		anterior = anterior->proximo;

	}
	
	return nullptr;

}
void FilaProcessos::imprimirFila() {
	Node* atual = head;
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
bool FilaProcessos::find(int pid) {
	if (head->processo->getPid() == pid) {
		return true;
	}

	Node* atual = head;
	while (atual != nullptr) {
		if (atual->processo->getPid() == pid)
			return true;
	}
	return false;
}

void FilaProcessos::salvarFila(ofstream& arquivo) {
	Node* atual = head;
	while (atual != nullptr) {
		atual->processo->save(arquivo);
		atual = atual->proximo;
	}
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
}

