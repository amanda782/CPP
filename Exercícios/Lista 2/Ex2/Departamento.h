#pragma once
#include <iostream>
#include <string>
#include "Funcionario.h"

using namespace std;

class Departamento {
public:
	Departamento();
	Departamento(string nome, Funcionario funcionarios[100]);
	~Departamento();


	string get_nome();
	bool inclui_funcionario(Funcionario& y);
	void dar_aumento_para_todos(float porcentagem);
	// Encontra um funcionário e retorna seu índice no array (-1 se não achar)
	int buscarFuncionarioPorNome(string& nomeFuncionario);
	// Retorna uma CÓPIA do funcionário em um dado índice
	Funcionario getFuncionario(int index);
	// Remove um funcionário pelo nome
	bool removerFuncionario(string& nomeFuncionario);

private:
	string nome_dep;
	Funcionario funcionarios_dep[100];
	int num_funcionarios;
	

};