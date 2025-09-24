#include "Jogador.h"  
#include "Entidade.h"
#include <cstdlib> // Para as funções srand() e rand()
#include <ctime>   // Para a função time()


Jogador::Jogador() { // construtor vazio com atributos válidos
	energia = 12;
	sorte  = 6;
	habilidade = 6;
	provisoes_atual_jogador = 0;
}

Jogador::Jogador(int energy, int luck, int hability, int provisoes) { // construtor que vai ser chamado após a definição da distribuição dos pontos
	energia = energy = 12;
	energiaMaxima = 24;
	sorte = luck = 6;
	habilidade = hability = 6;
	provisoes_atual_jogador = provisoes;
}

Jogador::~Jogador(){}

vector<Item> Jogador::get_inventario() {
	return inventario;
}

int Jogador::get_provisoes_atuais(){
	return provisoes_atual_jogador;
}

int Jogador::calcular_FA() {
	int forca_base = Entidade::calcular_FA(); // chama a função da entidade pra calcular a força base (comum ao inimigo, por isso está lá)
	int bonus_da_arma = this->arma_jogador.get_FA(); // dá um get no bônus da arma
	int forca_ataque = bonus_da_arma + forca_base; // soma o bônus da arma com a FA do jogador
	return forca_ataque; // retorna essa soma
	//caso o jogador não tenha uma arma, vai vir zero do construtor vazio e a soma continua válida!
}

bool Jogador::testar_sorte() {
	sorte--; // diminui uma unidade da sorte, já que está sendo utilizada
	int rolagem_sorte1 = (rand() % 7); //gera um número aleatório 1 a 6
	int rolagem_sorte2 = (rand() % 7); //gera outro número aleatório 1 a 6
	int rolagem_sorte_final = rolagem_sorte1 + rolagem_sorte2; // soma as duas rolagens. esse é o número que vamos comparar com a sorte do jogador

	if (sorte >= rolagem_sorte_final)
		return true;
	else
		return false;
}

bool Jogador::usar_provisao() {
	if (provisoes_atual_jogador >= 1) { // se o jogador tiver pelo menos uma provisão
		provisoes_atual_jogador--; // subtrai 1 provisão
		energia += 4; //e aumenta 4 pontos de vida
		if (energia > energiaMaxima)
			energia = energiaMaxima;
		return true;//a operação foi um sucesso!
	}
	else //provisões insuficientes, não foi possível efetuar a transação
		return false;
}

void Jogador::adiciona_item(Item novo_item) {
	inventario.push_back(novo_item); // adicionamos o novo item no vetor
	cout << "Você adicionou o item " << novo_item.get_nome() << "ao seu inventario!" << endl;
	//aviso pro usuário que o item foi adicionado ao inventário
}

void Jogador::adiciona_provisao(int quantidade_provisoes) {
	provisoes_atual_jogador = provisoes_atual_jogador + quantidade_provisoes; // atualiza as provisões com a quantidade passada por parâmetro
}

void Jogador::equipar_item(int indice_do_item) { // troca entre o inventário e o equipado
	if (indice_do_item < 0 || indice_do_item >= inventario.size()) {
		cout << "Opção inválida. ";
		return; //encerra a função se chegar aqui
	}
	else {
		Item item_para_equipar = this->inventario.at(indice_do_item); // at serve para acessar determinado item do vetor, entre parenteses a localização
		//aqui coloca na variável para_equipar o item que está no inventário no momento

		if (item_para_equipar.get_tipo() == 'w') { // se o item novo equipado for uma arma
			Item item_antigo = arma_jogador; // define a atual como antiga
			arma_jogador = item_para_equipar; // agora a equipada é a atual
			cout << "Você equipou: " << item_para_equipar.get_nome() << endl; // aviso que a arma nova foi equipada
			this->inventario.erase(this->inventario.begin() + indice_do_item); // o item equipado novo é removido do inventário

			if (item_antigo.get_nome() != "Item vazio") // se o item antigo for um item válido
				this->inventario.push_back(item_antigo); // ele é colocado de volta no inventário
		}
		else if (item_para_equipar.get_tipo() == 'a') { //se item novo for uma armadura
			Item item_antigo = armadura_jogador; // define a atual como antiga
			armadura_jogador = item_para_equipar; // agora a equipada é a atual
			cout << "Você equipou: " << item_para_equipar.get_nome() << endl; // aviso que a armadura nova foi equipada
			this->inventario.erase(this->inventario.begin() + indice_do_item); // o item equipado novo é removido do inventário

			if (item_antigo.get_nome() != "Item vazio") // se o item antigo for um item válido
				this->inventario.push_back(item_antigo); // ele é colocado de volta no inventário
		}
		else
			cout <<endl << item_para_equipar.get_nome() << "não é um item equipável" << endl;
	}
}

void Jogador::setProvisoes(int quantidade) {
	provisoes_atual_jogador = quantidade;
}

void Jogador::setTesouro(int quantidade) {
	tesouro = quantidade;
}

void Jogador::limparInventario() {
	inventario.clear(); // O metodo .clear() esvazia um vector
}

int Jogador::getTesouro() {
	return tesouro;
}
