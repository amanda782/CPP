#include "jogo.h"
#include"Entidade.h"
#include"Jogador.h"
#include"Inimigo.h"
#include"Item.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <cstdlib> // Necess�rio para srand()
#include <ctime>   // Necess�rio para time()

using namespace std;

int main() {
	srand(time(NULL));
	Jogo meuTeste;
	meuTeste.iniciarJogo();
	return 0;
}