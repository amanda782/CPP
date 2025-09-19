#include "jogo.h"

Jogo::Jogo() {
	idCenaAtual = 0;
	jogoRodando = false;
}

Jogo::~Jogo() {}

void Jogo::iniciarJogo() {
	idCenaAtual = 1;
	jogoRodando = true;
	while (jogoRodando == true) {
		cena.carregarCena(idCenaAtual); 
		if (cena.ehUmaBatalha() == true) {
			//iniciarBatalha(); //método ainda não foi criado
		}else (cena.ehUmaBatalha == false)
			// escolha() // tb não foi criado
	}
}

void Jogo::mostrarOpcoesEProcessarEscolha() {
	map<int, string> opcoes = cena.getOpcoes();
	cout << "\nO que voce faz?" << endl;
	cout << "------------------------------------------" << endl;
	}

