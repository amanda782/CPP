#pragma once
#include<string>
#include<iostream>
#include <sstream>

using namespace std; 


class CalculaExpressao
{
public:
	CalculaExpressao(string& expressao);
	CalculaExpressao();
	~CalculaExpressao();

	double calcular(); 

private: 
	double operando1;
	double operando2;
	char sinalOperacao; 

};

