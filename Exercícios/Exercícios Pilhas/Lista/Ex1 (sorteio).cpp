#include "Pilha.h"
#include <cstdlib>
#include <ctime>

int main() {
	//  "Semeia" o gerador de aleatórios com o tempo atual.
	srand(time(0));
	Pilha<int> p1;
	int resposta;
	cout << "Digite a quantidade de turnos: ";
	cin >> resposta;

	int lavador = (rand() % 5) + 1; // vai de 1 a 5
	int secador = (rand() % 3) + 1; // vai de 1 a 3

	int pratos_limpos = lavador * resposta;
	int pratos_secos = secador * resposta;

	for (int i = 0; i < pratos_limpos; i++) {
		p1.push(1);
	}
	for (int i = 0; i < pratos_secos; i++) {
		p1.pop();
	}

	int tamanho = p1.size();

	cout << "Quantidade total de pratos lavados: " << pratos_limpos << "( "<< lavador << ")" << endl;
	cout << "Quantidade total de pratos secos: " << pratos_secos << "( " << secador << ")"<< endl;
	cout << "Quantidade de pratos restantes na fila: " << tamanho << endl;

	return 0;
}