#pragma once
#include <iostream>
#include <string>
#include "Jogador.h"
#include "Cena.h"


using namespace std;

class Jogo {
public:
    Jogo();
    ~Jogo();

    void iniciarJogo(); //depende de todos os outros métodos 

    void mostrarTelaDeAbertura();//julie
    void criarNovoPersonagem();//amanda
    void mostrarOpcoesEProcessarEscolha(); // julie
    void iniciarBatalha(); // amanda
    void mostrarTelaDeCreditos(); //julie 
    void salvarJogo(); //julie
    bool carregarJogo();// julie


private:
    Jogador jogador;
    Cena cena;
    int idCenaAtual;
    bool jogoRodando;
    vector<int> cenasVisitadas;
};