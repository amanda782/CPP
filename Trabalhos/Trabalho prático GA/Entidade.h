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
    void setHabilidade(int hability);
    void setEnergia(int energy);
    void setSorte(int luck);

    virtual int calcular_FA();
    void setNome(string novoNome);
    int ajustarHabilidade(int quantidade);
    int ajustarEnergia(int quantidade);
    int ajustarSorte(int novaSorte);
    void setEnergiaMax(int novaEnergiaMax); // precisa para o carregarJogo()


protected:
	string nome;
    int habilidade;
    int energia;          
    int energiaMaxima;    
    int sorte; 

};
