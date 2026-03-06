#pragma once
#include <iostream>
#include <string>
#include "Departamento.h"

using namespace std;

class Empresa {
public:

	Empresa();
	Empresa(string nome, int cnpj);
	~Empresa();

	void inclui_departamento(Departamento &x);
	void transferirFuncionario( string& nomeFunc,  string& nomeDeptOrigem, string& nomeDeptDestino);
	Departamento* buscarDepartamentoPorNome( string& nomeDept);

private:
	string nome_empresa;
	int cnpj_emp;
	Departamento departamentos_emp[10];
	int num_departamentos;


};