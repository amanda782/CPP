#include"Cena.h"
#include <iostream>  
#include <fstream>   // Para poder ler arquivos (ifstream)
#include <sstream>   // Uma ferramenta util para processar strings

Cena::Cena(){
	textoDaHistoria = "";
	opcoes.clear(); // O metodo .clear() esvazia um map
	itensEncontrados.clear(); // e tambem um vector
	ehBatalha = false;
	idCenaVitoria = 0;
	idCenaDerrota = 0;
}

Cena::~Cena() {}

bool Cena::carregarCena(int numCena) {

}