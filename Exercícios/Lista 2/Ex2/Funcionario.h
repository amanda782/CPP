#pragma once
#include <iostream>
#include <string>

using namespace std;

class Funcionario {
public:
	Funcionario();
	Funcionario(string name, float salary, string data);
	~Funcionario();

	void dar_aumento(float porcentagem);
	string get_nome();


private:
	string nome;
	float salario;
	string data_admissao;

};