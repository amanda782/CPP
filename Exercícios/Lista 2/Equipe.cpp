#include "Equipe.h"
#include "Atleta.h"
#include "Esporte.h"
#include <iostream>

Equipe::Equipe() {
	conta_atletas = 0;
};

Equipe::Equipe(string nome, Esporte esporte_praticado) {
	nome_da_equipe = nome;
	esporte_da_equipe = esporte_praticado;
	conta_atletas = 0;
}

Equipe::~Equipe() {};

void Equipe::adicionar_atleta(const Atleta& novo_atleta) {
	if (conta_atletas < 30) {
		vetorAtletas[conta_atletas] = novo_atleta;
		conta_atletas++;

		cout << "Atleta adicionado com sucesso! " << endl;

	}
	else
		cout << "Erro! A equipe já está cheia. " << endl;
}

void Equipe::exibir_equipe() {
	esporte_da_equipe.imprime_info(); // esporte que pertence a equipe

	cout << "Atletas da equipe: ";

	if (conta_atletas == 0) {
		cout << endl << "Nenhum atleta foi adicionado a equipe ainda. " << endl;

	}
	else {
		for (int i = 0; i < conta_atletas; i++) {
			vetorAtletas[i].imprime_info();
		}
	}

};
