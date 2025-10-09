#include"Entidade.h"

Entidade::Entidade() {
	nome = "";
	habilidade = 0; //6
	sorte = 0; //6
	energia = 0; //12
	energiaMaxima = 0;

	//não dá pra fazer o inicio de ptos AQUI, porque se não os inimigos iniciarão igual jogador sempre. 
}
Entidade::Entidade(string name, int ability, int energy, int luck) {
	nome = name;
	habilidade = ability;
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

int Entidade::ajustarHabilidade(int quantidade) {
	habilidade += quantidade;
	if (habilidade > 12) {
		cout << "A habilidade ultrapassou o limite. Agora, voce possui 12 pontos de habilidade." << endl << endl;
		int habilidade_ultrapassada = habilidade; // salva o valor total, com a soma ultrapassando o limite
		habilidade = 12; // define a habilidade como maxima (12)
		return habilidade_ultrapassada - 12; // retorna a quantidade de pontos nao utilizados
	}
	else {
		cout << "Habilidade redefinida. Agora voce possui " << habilidade << " pontos de habilidade." << endl << endl;//imprime a habilidade atual
		return 0; // nao sobrou nenhum ponto não utilizado
	}
}

int Entidade::ajustarEnergia(int quantidade) {
	energia += quantidade;
	if (energia > 24) {
		cout << "A energia ultrapassou o limite. Agora, voce possui 24 pontos de energia." << endl << endl;
		int energia_ultrapassada = energia; // salva o valor total, com a soma ultrapassando o limite
		energia = 24; // define a energia como maxima (24)
		return energia_ultrapassada - 24; // retorna a quantidade de pontos nao utilizados
	}
	else {
		cout << "Energia redefinida. Agora voce possui " << energia << " pontos de energia." << endl << endl; //imprime a energia atual
		return 0; // nao sobrou nenhum ponto não utilizado
	}
}

int Entidade::ajustarSorte(int quantidade) {
	sorte += quantidade; // adiciona a quantidade especificada pelo player na classe jogo
	if (sorte > 12) {
		cout << "A sorte ultrapassou o limite. Agora, voce possui 12 pontos de sorte." << endl << endl;
		int sorte_ultrapassada = sorte; // salva o valor total, com a soma ultrapassando o limite
		sorte = 12; // define a sorte como maxima (12)
		return sorte_ultrapassada - 12; // retorna a quantidade de pontos nao utilizados
	}
	else {
		cout << "Sorte redefinida. Agora voce possui " << sorte << " pontos de sorte." << endl << endl; //imprime a sorte atual
		return 0; // nao sobrou nenhum ponto não utilizado
	}
	
}

void Entidade::setEnergiaMax(int novaEnergiaMax) {
	energiaMaxima = novaEnergiaMax;
}

int Entidade::calcular_FA() {
	int rolagem_dado = (rand() % 10) + 1; // gera um número aleatório entre 1 e 10
	int forca_de_ataque = habilidade + rolagem_dado; //soma  a habilidade com a rolagem do dado
	return forca_de_ataque;
 }

void Entidade::setHabilidade(int hability) {
	habilidade = hability;
}

void Entidade::setEnergia(int energy) {
	energia = energy;
}
void Entidade::setSorte(int luck) {
	sorte = luck;
}

