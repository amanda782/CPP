#include"Entidade.h"

Entidade::Entidade() {
	nome = "";
	habilidade = 0;
	sorte = 0;
	energia = 0;
	energiaMaxima = 0;
}
Entidade::Entidade(string name, int ability, int energy, int luck) {
	nome = name;
	habilidade = ability = 6;
	energiaMaxima = energy;
	energia = energiaMaxima;
	sorte = luck;
}

Entidade::~Entidade() {}

void Entidade::receberDano(int dano) {
	energia -= dano;
	if (energia < 0) {
		energia = 0;
	}
}

bool Entidade:: estaVivo(){
	if (energia > 0)
		return true;
	else
		return false;
}
string Entidade::getNome() {
	return nome;
}
int Entidade::getHabilidade() {
	return habilidade;
}
int Entidade::getEnergia() {
	return energia;
}
int Entidade::getEnergiaMax() {
	return energiaMaxima;
}
int Entidade::getSorte() {
	return sorte;
}

void Entidade::setNome(string novoNome) {
	nome = novoNome;
}

void Entidade::setHabilidade(int novaHabilidade) {
	habilidade = novaHabilidade;
}

void Entidade::setEnergia(int novaEnergia) {
	energia = novaEnergia;
}

void Entidade::setSorte(int novaSorte) {
	// A responsabilidade desta função é definir o valor da sorte
	// Regras complexas são responsabilidade da lógica do jogo
	// A única validação importante aqui é garantir que o atributo não fique negativo
	if (novaSorte < 6) {
		sorte = 6;
	}
	else {
		sorte = novaSorte;
	}
}

void Entidade::setEnergiaMax(int novaEnergiaMax) {
	energiaMaxima = novaEnergiaMax;
}

int Entidade::calcular_FA() {
	int rolagem_dado = (rand() % 10) + 1; // gera um número aleatório entre 1 e 10
	int forca_de_ataque = this->habilidade + rolagem_dado; //soma  a habilidade com a rolagem do dado
	return forca_de_ataque;
 }
