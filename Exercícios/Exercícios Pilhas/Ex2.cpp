#include <iostream>
#include <stack>
using namespace std;

int main() {
	stack<char> palavra;
	string resposta;
	cout << "Digite a palavra que deseja reverter: " << endl;
	cin >> resposta;

	for (char elemento : resposta) {
		palavra.push(elemento);
	}
	cout << "Palavra invertida: ";
	while (!palavra.empty()) {
		cout << palavra.top();
		palavra.pop();
	}

	return 0;
}