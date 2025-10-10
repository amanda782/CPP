#include "jogo.h"
#include"Entidade.h"
#include"Jogador.h"
#include"Inimigo.h"
#include"Item.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <cstdlib> // Necessário para srand()
#include <ctime>   // Necessário para time()

using namespace std;

int main() {
	srand(time(NULL));
	Jogo meuTeste;
	meuTeste.iniciarJogo();
	return 0;
}