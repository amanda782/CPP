#include "Pilha.h"

int main() {
	Pilha<char> p1;
	string s = "arara";

	for (char c : s) {
		p1.push(c);
	}
	string nova;
	while (p1.topNode() != nullptr) {
		char novo = p1.top();
		nova += novo;//add no final da string o proximo caractere
		p1.pop();
	}

	cout << "String original:  " << s << endl;
	cout << "String invertida: " << nova << endl;

	if (s == nova) {
		cout << "A palavra eh um palindromo " << endl;
	}
	else {
		cout << "A palavra nao eh um palindromo" << endl;
	}
	return 0;
}