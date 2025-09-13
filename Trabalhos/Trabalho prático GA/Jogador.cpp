#include "Jogador.h"  
#include "Entidade.h"
#include <cstdlib> // Para as fun��es srand() e rand()
#include <ctime>   // Para a fun��o time()


Jogador::Jogador() {
	energia_atual_jogador = 0;
	sorte_atual_jogador = 0;
	habilidade_jogador = 0;
	provisoes_atual_jogador = 0;
}

Jogador::Jogador(int energia, int sorte, int habilidade, int provisoes) { // vai ser setado com o m�nimo no come�o
	energia_atual_jogador = energia;
	sorte_atual_jogador = sorte;
	habilidade_jogador = habilidade;
	provisoes_atual_jogador = provisoes;
}

Jogador::~Jogador(){}

int Jogador::get_provisoes_atuais(){
	return provisoes_atual_jogador;
}

int Jogador::calcular_FA() {

}

