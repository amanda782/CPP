#include "Fila.h"

int main() {
	Fila<int> f1;
	f1.push(2);
	f1.push(3);
	f1.removerEspecifico(3);
	bool answer = f1.isEmpty();
	cout << answer << endl;
	f1.print();
	return 0;
}