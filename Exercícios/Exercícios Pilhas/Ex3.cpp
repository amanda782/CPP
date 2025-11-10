#include <iostream>
#include <stack>

using namespace std;
stack<char> palavra;

void verificaPalindromo(string& resposta) {
	for (char elemento : resposta) {
		palavra.push(elemento);
	}

	for (int i = 0; i < palavra.size(); i++) {
		if (palavra.top() == resposta[i]) {
			palavra.pop();
		}
		else {
			cout << "A palavra NAO e palindromo." << endl;
			return;
		}
	}

	cout << "A palavra e um palindromo!" << endl;
	
}
int main() {
	
	cout << "Digite a palavra para verificarmos se e palindromo: " << endl;
	string resposta;
	cin >> resposta;
	verificaPalindromo(resposta);
	return 0;

	
}