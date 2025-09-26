#include "Departamento.h"
#include "Funcionario.h"

Departamento::Departamento(){}

Departamento::Departamento(string nome, Funcionario funcionarios[100]) {
	nome_dep = nome;
	funcionarios_dep[100] = funcionarios[100];
	num_funcionarios = 0;
}

Departamento::~Departamento(){}

bool Departamento::inclui_funcionario(Funcionario& y) {
	if (num_funcionarios < 100) {
		funcionarios_dep[num_funcionarios] = y;
		num_funcionarios++;
		return true;
	}
	else
		return false;
}

void Departamento::dar_aumento_para_todos(float porcentagem) {
	int i = 0;
	while (i < (num_funcionarios )) {
		funcionarios_dep[i].dar_aumento(porcentagem);
	}
}

// Encontra um funcionário e retorna seu índice no array (-1 se não achar)
int Departamento::buscarFuncionarioPorNome(string &nomeFuncionario) {
	for (int i = 0; i < num_funcionarios; i++) {
		if (nomeFuncionario== funcionarios_dep[i].get_nome())
			return i;
		return -1; // se nao achar retorna -1
	}
}

Funcionario Departamento::getFuncionario(int index) {
	if (index >= 0 && index < num_funcionarios) {
		return funcionarios_dep[index];
	}
	return Funcionario();
}

string Departamento::get_nome() {
	return nome_dep;
}

bool Departamento::removerFuncionario(string& nomeFuncionario) {
	int index = buscarFuncionarioPorNome(nomeFuncionario);

	if (index != -1) { // Se encontrou o funcionário...
		// Para "apagar" o funcionário, nós deslocamos todos os funcionários
		// que vêm depois dele uma posição para a esquerda.
		for (int i = index; i < num_funcionarios - 1; ++i) {
			funcionarios_dep[i] = funcionarios_dep[i + 1];
		}
		num_funcionarios--; // Decrementa o contador
		return true;
	}
	return false; // Não encontrou o funcionário para remover
}