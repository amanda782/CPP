#include "Fila.h"
Fila<int> estacionamento;

void inserir(int placa) { // inserir no final da fila
	estacionamento.push(placa);
}

void retirar(int placa) { //remove do meio da fila, colocando todo mundo pra tras
	if (!estacionamento.find(placa)) {
		cout << "Placa nao encontrada no estacionamento." << endl;
		return;
	}
		
		if (estacionamento.front() == placa) {// nesse caso, só remove o primeiro
			estacionamento.pop();
			return;
		}
		else {
			bool encontrado = false;
			while (!encontrado) {
				int carro = estacionamento.front();
				if (carro == placa) {
					estacionamento.pop();
					encontrado = true;
				}
				else {
					estacionamento.pop();
					estacionamento.push(carro);
				}
			}
		}
}

int main() {
	cout << "BEM-VINDO AO ESTACIONAMENTO DO MANOEL" << endl;

	while (1) {
		char resposta;
		cout << "O que voce deseja fazer?" << endl;
		cout << "1: Adicionar um carro ao estacionamento" << endl;
		cout << "2: Remover um carro do estacionamento" << endl;
		cout << "S: Imprimir a fila de carros" << endl;
		cin >> resposta;
		int placa;
		switch(resposta) {
		case '1':
			cout << "Digite o numero da placa que deseja inserir: " << endl;
			cin >> placa;
			inserir(placa);
			break;
		case '2':
			cout << "Digite o numero da placa que deseja remover: " << endl;
			cin >> placa;
			retirar(placa);
			break;
		case 'S':
			estacionamento.print();
			break;
		}
	}

}