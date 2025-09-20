#pragma once
#include<iostream>
#include<string>

using namespace std;

class Entidade {
public:
	Entidade();
	Entidade(string name, int ability, int energy, int luck);
	~Entidade();

    void receberDano(int dano);
    bool estaVivo();

    string getNome();
    int getHabilidade();
    int getEnergia();
    int getEnergiaMax();
    int getSorte();
    virtual int calcular_FA();
    void setNome(string novoNome);
    void setHabilidade(int novaHabilidade);
    void setEnergia(int novaEnergia);
    void setSorte(int novaSorte);
    void setEnergiaMax(int novaEnergiaMax); // precisa para o carregarJogo()


protected:
	string nome;
    int habilidade;
    int energia;          
    int energiaMaxima;    
    int sorte;            

};
