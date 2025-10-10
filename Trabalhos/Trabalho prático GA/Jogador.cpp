#include "Jogador.h"  
#include "Entidade.h"
#include <cstdlib> // Para as fun��es srand() e rand()
#include <ctime>   // Para a fun��o time()
#include "Item.h"
#include "jogo.h"
#include "Cena.h"
#include "Entidade.h"





Jogador::Jogador() :Entidade ("Harry Potter", 6, 12, 6) { // construtor vazio com atributos v�lidos
	provisoes_atual_jogador = 0;
	tesouro = 0;
}

Jogador::Jogador(string name, int energy, int luck, int hability, int provisoes) :Entidade(name, hability, energy, luck) { // construtor que vai ser chamado ap�s a defini��o da distribui��o dos pontos
	provisoes_atual_jogador = provisoes;
	tesouro = 0;
	Item varinhaInicial("Varinha", 'w', true, 1, 2); // nome, tipo, combate, FA, dano
	arma_jogador = varinhaInicial;
}

Jogador::~Jogador(){}

vector<Item> Jogador::get_inventario() {
	return inventario;
}

int Jogador::get_provisoes_atuais(){
	return provisoes_atual_jogador;
}

Item Jogador::getArmaEquipada() {
	return arma_jogador;
}
void Jogador::imprime_inventario() {

	// Imprime os status principais primeiro
	cout << "--- STATUS ---" << endl;
	cout << "Nome: " << nome << endl;
	cout << "Habilidade: " << habilidade << endl;
	cout << "Sorte: " << sorte << endl;
	cout << "Energia: " << energia << " / " << energiaMaxima << endl;
	cout << "Provisoes: " << provisoes_atual_jogador << endl;
	cout << "Tesouro: " << tesouro << endl;
	cout << "------------------" << endl;

	// Imprime a arma e armadura equipadas
	if (arma_jogador.get_nome() != "Item vazio") {
		cout << "Arma Equipada: " << arma_jogador.get_nome() << endl;
	}
	if (armadura_jogador.get_nome() != "Item vazio") {
		cout << "Armadura Equipada: " << armadura_jogador.get_nome() << endl;
	}

	// Imprime os itens no invent�rio
	cout << "--- ITENS NA MOCHILA ---" << endl;
	if (inventario.empty()) {
		cout << "A mochila esta vazia." << endl;
	}
	else {
		for (size_t i = 0; i < inventario.size(); ++i) {
			Item& item_atual = inventario[i];
			string tipo_texto;
			switch (item_atual.get_tipo()) {
			case 'w': tipo_texto = "Arma"; break;
			case 'a': tipo_texto = "Armadura"; break; 
			case 'c': tipo_texto = "Comum"; break;
			default: tipo_texto = "Desconhecido"; break;
			}
			cout << i + 1 << ". " << item_atual.get_nome()
				<< " [" << tipo_texto << "]"
				<< " (FA: " << item_atual.get_FA()
				<< ", Dano: " << item_atual.get_dano() << ")" << endl;
		}
	}
	cout << "------------------" << endl;

	cout << "\nPressione Enter para continuar...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de forma segura
	cin.get();
}


int Jogador::calcular_FA() {
	int forca_base = Entidade::calcular_FA(); // chama a fun��o da entidade pra calcular a for�a base (comum ao inimigo, por isso est� l�)
	int bonus_da_arma = arma_jogador.get_FA(); // d� um get no b�nus da arma
	int forca_ataque = bonus_da_arma + forca_base; // soma o b�nus da arma com a FA do jogador
	return forca_ataque; // retorna essa soma
	//caso o jogador n�o tenha uma arma, vai vir zero do construtor vazio e a soma continua v�lida!
}

bool Jogador::testar_sorte() {
	sorte--; // diminui uma unidade da sorte, j� que est� sendo utilizada
	int rolagem_sorte1 = (rand() % 6) +1 ; //gera um n�mero aleat�rio 1 a 6
	int rolagem_sorte2 = (rand() % 6) + 1; //gera outro n�mero aleat�rio 1 a 6
	int rolagem_sorte_final = rolagem_sorte1 + rolagem_sorte2; // soma as duas rolagens. esse � o n�mero que vamos comparar com a sorte do jogador
	cout << "Numero sorteado: " << rolagem_sorte_final << endl;
	cout << "Seu numero de sorte:" << sorte << endl;

	if (sorte >= rolagem_sorte_final) {
		cout << "A sorte esta do seu lado! Dano reduzido em 2x." << endl;
		cout << endl << "Pressione enter para continuar. " << endl;
		cin.get();
		return true;
	}
	else {
		cout << "Mais sorte na proxima. Infelizmente nao foi dessa vez :( " << endl;
		cout << endl << "Pressione enter para continuar. " << endl;
		cin.get();
		return false;
	}
}


bool Jogador::usar_provisao() {
	// Procura pelo item "Sapo de Chocolate" no invent�rio
	for (int i = 0; i < inventario.size(); ++i) {
		if (inventario[i].get_nome() == "Sapo de Chocolate") {

			// Efeito da provis�o
			energia += 4;
			if (energia > energiaMaxima) {
				energia = energiaMaxima;
			}

			// Remove o item do invent�rio ap�s o uso
			inventario.erase(inventario.begin() + i);

			cout << "\nVoce comeu um Sapo de Chocolate e recuperou 4 de energia!" << endl;
			return true; // Sucesso!
		}
	}

	// Se o loop terminar, significa que n�o encontrou o item
	cout << "\nVoce nao tem Sapo de Chocolate para usar!" << endl;
	return false; // Falha!
}

void Jogador::adiciona_item(Item novo_item) {
	inventario.push_back(novo_item); // adicionamos o novo item no vetor

}

void Jogador::adiciona_provisao(int quantidade_provisoes) {
	provisoes_atual_jogador = provisoes_atual_jogador + quantidade_provisoes; // atualiza as provis�es com a quantidade passada por par�metro
}

void Jogador::equipar_item(int indice_do_item) { // troca entre o invent�rio e o equipado
	if (indice_do_item < 0 || indice_do_item >= inventario.size()) {
		cout << "Op��o inv�lida. ";
		return; //encerra a fun��o se chegar aqui
	}
	else {
		Item item_para_equipar = inventario.at(indice_do_item); // at serve para acessar determinado item do vetor, entre parenteses a localiza��o
		//aqui coloca na vari�vel para_equipar o item que est� no invent�rio no momento

		if (item_para_equipar.get_tipo() == 'w') { // se o item novo equipado for uma arma
			Item item_antigo = arma_jogador; // define a atual como antiga
			arma_jogador = item_para_equipar; // agora a equipada � a atual
			cout << "Voc� equipou: " << item_para_equipar.get_nome() << endl; // aviso que a arma nova foi equipada
			inventario.erase(inventario.begin() + indice_do_item); // o item equipado novo � removido do invent�rio

			if (item_antigo.get_nome() != "Item vazio") // se o item antigo for um item v�lido
				inventario.push_back(item_antigo); // ele � colocado de volta no invent�rio
		}
		else if (item_para_equipar.get_tipo() == 'a') { //se item novo for uma armadura
			Item item_antigo = armadura_jogador; // define a atual como antiga
			armadura_jogador = item_para_equipar; // agora a equipada � a atual
			cout << "Voc� equipou: " << item_para_equipar.get_nome() << endl; // aviso que a armadura nova foi equipada
			inventario.erase(inventario.begin() + indice_do_item); // o item equipado novo � removido do invent�rio

			if (item_antigo.get_nome() != "Item vazio") // se o item antigo for um item v�lido
				inventario.push_back(item_antigo); // ele � colocado de volta no invent�rio
		}
		else
			cout <<endl << item_para_equipar.get_nome() << "n�o � um item equip�vel" << endl;
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

bool Jogador::usar_sorte() {
	if (sorte > 0) {
		sorte--;
		return true;
	}
	else {
		cout << "Voce nao possui pontos de sorte disponiveis." << endl;
		return false;
	}
}

int Jogador::ampliar_dano( int dano_ampliar) {
	bool sorteado = usar_sorte();
	if (sorteado) {
		dano_ampliar = dano_ampliar * 2;
		cout << "A sorte esta do seu lado! Dano ampliado em 2x." << endl;
	}
	else
		cout << "Mais sorte na proxima. Infelizmente nao foi dessa vez :( " << endl;

	return dano_ampliar;
}

int Jogador::reduzir_dano(int dano_reduzir) {
	bool good_luck = usar_sorte();
	if (good_luck) {
		dano_reduzir = dano_reduzir / 2;
		
	}
	return dano_reduzir;
}
