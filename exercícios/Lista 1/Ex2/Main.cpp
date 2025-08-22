#include "Cabeçalho.h"

int main() {


	Pessoa p1("Amanda", 19, 161, 1, "Campo Bom");
	Pessoa p2("Julie", 18, 164, 0, "Cachoeirinha");
	Pessoa p3("Luan", 21, 181, 2, "Esteio");

	p1.imprime_info();
	if (p1.is_filho_unico())
		cout << "Filho unico" << endl << endl;
	else
		cout << "Nao e filho unico" << endl << endl;

	p2.imprime_info();
	if (p2.is_filho_unico())
		cout << "Filho unico" << endl << endl;
	else
		cout << "Nao e filho unico" << endl << endl;

	p3.imprime_info();
	if (p3.is_filho_unico())
		cout << "Filho unico" << endl << endl;
	else
		cout << "Nao e filho unico" << endl << endl;





	return 0;

}
