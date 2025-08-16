#include "Pessoa.h"

int main() {
	

	string n; int id; int alt; int irm; string end;

	cout << "Digite o nome: " << endl;
		cin >> n;

	cout << "Digite a idade: " << endl;
		cin >> id;
		
	cout << "Digite a altura: " << endl;
		cin >> alt;

	cout << "Digite a quantidade de irmaos: " << endl;
		cin >>irm;

	cout << "Digite o endereço: " << endl;
		cin >> end;

		Pessoa p(n, id, alt, irm, end);

		p.imprime_info();

		

		return 0;
		

		





}

