#pragma once
#include <string>
#include <vector>
#include <map> // Precisamos do 'map' para guardar as opções de escolha, ele é tipo um dicionario, que nesse caso aqui, vai relacionar um numero c um texto.
#include "Inimigo.h"
#include "Item.h"

class Cena {
public:
	Cena();
	~Cena();

    bool carregarCena(int numeroDaCena);

    string getTextoDaHistoria();
    map<int, string>& getOpcoes();
    Inimigo getInimigo();
    bool ehUmaBatalha();
    int getIdCenaVitoria();
    int getIdCenaDerrota();
    vector<Item> getItensEncontrados();

private: 
    string textoDaHistoria;
    map<int, string> opcoes; 
    Inimigo inimigo;
    bool ehBatalha;
    int idCenaVitoria; // guarda os valores das cenas de vitoria, p ir dps
    int idCenaDerrota; // guarda o valor da cena de derrota, p ir dps 
    vector<Item> itensEncontrados;
};
