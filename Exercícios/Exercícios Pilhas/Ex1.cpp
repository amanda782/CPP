#include <iostream>
#include <stack>
using namespace std;

stack <char> pilha;

void insere(char elemento) {
	pilha.push(elemento);
}

void remove(char elemento) {
	if (!pilha.empty()) {
		pilha.pop();
		cout << "Ultimo elemento removido com sucesso" << endl;
	}
	else
		cout << "A pilha ja esta vazia" << endl;
}

void busca(char elemento) {
	stack<char> aux;
	bool visto = false;
	while (!pilha.empty()) { // destruindo a stack original
		if (pilha.top() == elemento) {
			visto = true;
			cout << "Elemento encontrado na pilha. " << endl;
			break;
		}
		else {
			char novo = pilha.top();
			pilha.pop();
			aux.push(novo);
		}
	}
	while (!aux.empty()) { // reconstruindo a stack original
		char novo = aux.top();
		pilha.push(novo);
		aux.pop();
	}
		
}

void imprime() {
	stack<char> aux;
	while (!pilha.empty()) {
		char novo = pilha.top();
		cout << novo << " ";
		aux.push(novo);
		pilha.pop();
	}
	while (!aux.empty()) {
		char topo = aux.top();
		pilha.push(topo);
		aux.pop();
	}
}
int main() {
	while (1) {
		cout << "Digite qual operacao deseja realizar: " << endl;
		cout << "1: Inserir um elemento a pilha" << endl;
		cout << "2: Remover o elemento do topo" << endl;
		cout << "3: Buscar um elemento na pilha" << endl;
		cout << "4: Imprimir a pilha" << endl;
		cout << "5: Encerrar o programa" << endl;
		int resposta;
		char elemento;
		cin >> resposta;
		switch (resposta) {

		case 1:
			cout << "Digite o elemento que deseja inserir:" << endl;
			cin >> elemento;
			insere(elemento);
			break;
		case 2:
			cin >> elemento;
			remove(elemento);
			break;
		case 3:
			cout << "Digite o elemento que deseja buscar:" << endl;
			cin >> elemento;
			busca(elemento);
			break;
		case 4:
			imprime();
			break;
		case 5: 
			return 0;

		}

	}
}