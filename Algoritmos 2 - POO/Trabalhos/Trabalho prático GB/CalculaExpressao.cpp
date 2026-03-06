#include "CalculaExpressao.h"

CalculaExpressao::CalculaExpressao() {
	operando1 = 0;
	operando2 = 0;
	sinalOperacao = ' ';
}

CalculaExpressao::CalculaExpressao(string& expressao) {
	
    //faz o stringstream direto no construtor pro objeto ser criado só quando já tiver quebrado 

	stringstream ss(expressao);
	ss >> operando1;     // O stream 'ss' lê e coloca em operando1
	ss >> sinalOperacao;      // O stream 'ss' ignora o espaço, lê e coloca em operacao
	ss >> operando2;     // O stream 'ss' ignora o espaço, lê e coloca em operando2
}

CalculaExpressao::~CalculaExpressao() {}

double CalculaExpressao::calcular() {

    switch (sinalOperacao) {
    case '+':
        return operando1 + operando2;
    case '-':
        return operando1 - operando2;
    case '*':
        return operando1 * operando2;
    case '/':
        if (operando2 == 0) {
            cerr << "Erro: Tentativa de divisao por zero!" << endl;
            return 0.0; // retorna 0.0 em caso de erro pq eh double
        }
        return operando1 / operando2;
    default:
        cout << "Erro: Operacao invalida. Nao foi possivel executar esse calculo. " << endl;
        return 0.0; 
    }
}
