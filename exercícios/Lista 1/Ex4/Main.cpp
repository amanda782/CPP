#include "Calculadora.h"
#include "FuncionarioCaixa.h"
#include "Empresa.h"


int main() {
	Calculadora c1("vermelho");
	Calculadora c2("rosa");
	
	FuncionarioCaixa f1("Amanda", "Campo Bom", c1);
	FuncionarioCaixa f2("Julie", "Cachoeirinha", c2);

	float soma1 = f1.soma(2, 2);
	float sub1 = f1.subtracao(5, 4);
	float mult1 = f1.multiplicacao(2, 3);

	float div1 = f2.divisao(6, 3);
	float soma2 = f2.soma(7, 2);
	float mult2 = f2.multiplicacao(8, 2);

	cout << soma1 << endl << sub1 << endl << mult1 << endl << div1 << endl << soma2 << endl << mult2 << endl;
	
	//imprimir os resultados

	Empresa X1("Jumanda", f1, f2);
	X1.imprime_info();


	f1.imprime_info();
	f2.imprime_info();

	c1.imprime_info();
	c2.imprime_info();


	return 0;
}