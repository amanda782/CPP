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
	// Encontra um funcion�rio e retorna seu �ndice no array (-1 se n�o achar)
	int buscarFuncionarioPorNome(string& nomeFuncionario);
	// Retorna uma C�PIA do funcion�rio em um dado �ndice
	Funcionario getFuncionario(int index);
	// Remove um funcion�rio pelo nome
	bool removerFuncionario(string& nomeFuncionario);

private:
	string nome_dep;
	Funcionario funcionarios_dep[100];
	int num_funcionarios;
	

};