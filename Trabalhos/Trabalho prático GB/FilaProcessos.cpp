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
Processo* FilaProcessos::removerPorPid(int pid) {
	if (head == nullptr) // se for uma lista vazia
		return nullptr; // retorna nada

	else if (head->processo->getPid() == pid) { // nesse caso removemos o primeiro
		return removerProximo();  // e ja temos metodo pra isso!!
	}

	else{
		int voltas = tamanho;
		bool jaRemoveu = false;
		Processo* retornar = nullptr;
		for (int i = 0; i < voltas; i++) {
			//tira o primeiro
			Processo* removido = this->removerProximo();

			//é o que queremos remover? e ainda não removemos?
			if (removido->getPid() == pid && !jaRemoveu) {
				// entao uardamos o valor e NÃO devolvemos para a fila (push)
				retornar = removido;
				jaRemoveu = true; // a partir daqui, nunca mais entra nessa verificacao/bloco de codigo
				// o item foi removido pois não demos push
			}
			else {
				//caso nao seja oq queremos, devolvemos para o final da fila
				this->inserir(removido); //pusha o elemento que acabei de tirar do fim da fila
			}
		}

		return retornar;
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
	Node* atual = head;

	while (atual != nullptr) {
		if (atual->processo->getPid() == pid)
			return true;

		atual = atual->proximo;
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
	tamanho = 0;
}

int FilaProcessos::size() {
	return tamanho;
}
