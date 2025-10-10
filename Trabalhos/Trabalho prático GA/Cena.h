#pragma once
#include <string>
#include <vector>
#include <map> // Precisamos do 'map' para guardar as op��es de escolha, ele � tipo um dicionario, que nesse caso aqui, vai relacionar um numero c um texto.
#include "Inimigo.h"
#include "Item.h"
#include "Jogador.h"

class Cena {
public:
	Cena();
	~Cena();

    bool carregarCena(int numeroDaCena, Jogador& jogador);

    string getTextoDaHistoria();
    map<int, string> getOpcoes();
    Inimigo& getInimigo();
    bool ehUmaBatalha(); //exp�e se � ou n�o 
    int getIdCenaVitoria();
    int getIdCenaDerrota();
    int getIdCenaAtual();
    vector<Item> getItensEncontrados();
    bool ehTesteDeSorte();

private: 
    string textoDaHistoria;
    map<int, string> opcoes; // opcoes � uma vari�vel do tipo map<int, string> porque ela guarda o map, que nesse caso associa, inteiros e textos.
    Inimigo inimigo;
    bool ehBatalha; //guarda se � ou n�o 
    int idCenaVitoria; // guarda os valores das cenas de vitoria, p ir dps
    int idCenaDerrota; // guarda o valor da cena de derrota, p ir dps 
    int idCenaAtual; 
    vector<Item> itensEncontrados;
    bool ehUmTesteDeSorte;

};
