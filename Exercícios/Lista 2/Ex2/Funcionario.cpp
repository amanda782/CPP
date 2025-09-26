#include "Funcionario.h"

Funcionario::Funcionario() {

}

Funcionario::Funcionario(string name, float salary, string data) {
	nome = name;
	salario = salary;
	data_admissao = data;
}

Funcionario::~Funcionario(){}

string Funcionario::get_nome() {
	return nome;
}

void Funcionario::dar_aumento(float porcentagem) {
	if (porcentagem > 0) {
		salario += salario * (porcentagem / 100);
	}
}
