#include"Cena.h"
#include <iostream>  
#include <fstream>   // Para poder ler arquivos (ifstream)
#include <sstream>   // Uma ferramenta util para processar strings
#include "Jogador.h"
#include "jogo.h"

Cena::Cena(){
	textoDaHistoria = "";
	opcoes.clear(); // O metodo .clear() esvazia um map
	itensEncontrados.clear(); // e tambem um vector
	ehBatalha = false;
	ehUmTesteDeSorte = false; 
	idCenaVitoria = 0;
	idCenaDerrota = 0;
	idCenaAtual = 0; 
}

Cena::~Cena() {}

bool Cena::carregarCena(int numeroDaCena, Jogador& jogador) {

	if (numeroDaCena == 0) //retorna 0 caso va pra cena 0 (final)
		return false;

	textoDaHistoria = "";
	opcoes.clear(); // O metodo .clear() esvazia um map
	itensEncontrados.clear(); // e tambem um vector
	ehBatalha = false;
	idCenaVitoria = 0;
	idCenaDerrota = 0;
	ehUmTesteDeSorte = false;

	//to_string é uma função padrão do C++ que converte um número (int) em uma string.
	string nomeDoArquivo = to_string(numeroDaCena) + ".txt"; //numeroDaCena, vamos passar por parâemtro na classe jogo.
	ifstream arquivo(nomeDoArquivo); // ifstream cria um leitor de arquivos


	if (!arquivo.is_open()) {
		cout << "ERRO: Nao foi possivel abrir o arquivo da cena: " << nomeDoArquivo << endl;
		return false;
	}

	string linha;

	while (getline(arquivo, linha))//getline lê a linha do arquivo e armazena na variavel linha
	{
		if (linha.rfind("#", 0) == 0) { //procura o # desde a posição 0

			// Encontra a posição dos dois pontos
			size_t coloca_dois_pontos = linha.find(':');

			// Se não tiver ":", pula a linha (evita erro)
			if (coloca_dois_pontos == string::npos) continue;

			// Pega o número da cena (entre '#' e ':')
			string parte_numero = linha.substr(1, coloca_dois_pontos - 1);

			// Se estiver vazio, pula a linha (evita stoi(""))
			if (parte_numero.empty()) continue;

			// Converte o número da cena
			int id_proxima_cena = stoi(parte_numero);

			// Pega o texto da escolha (depois dos ':')
			string parte_texto = linha.substr(coloca_dois_pontos + 2);

			// Armazena no mapa de opções
			opcoes[id_proxima_cena] = parte_texto;
		}

		else if (linha == "M: S") { 

			ehBatalha = true;       
		}

		else if (linha.rfind("N: ", 0) == 0) {

			
			string nome_do_inimigo = linha.substr(3); //pegamos a string apartir da posicao 3 (depois do espaço) pq é onde inicia o nome do monstro
			inimigo.setNome(nome_do_inimigo); // passamos o nome do inimigo por setter
		
		}
				
		else if (linha.rfind("H: ", 0) == 0) {

			string parte_habilidade = linha.substr(3); //pega o numero da habilidade
			int valor_habilidade = stoi(parte_habilidade);// transforma o numero em int
			inimigo.setHabilidade(valor_habilidade);//seta o valor da habilidade do inimigo 

		}

		else if (linha.rfind("S: ", 0) == 0) {

			string parte_sorte = linha.substr(3); //pega o numero da sorte
			int valor_sorte = stoi(parte_sorte);// transforma o numero em int
			inimigo.setSorte(valor_sorte);//seta o valor da sorte do inimigo 

		}

		else if (linha.rfind("E: ", 0) == 0) {

			string parte_energia = linha.substr(3); //pega o numero da energia 
			int valor_energia = stoi(parte_energia);// transforma o numero em int
			inimigo.setEnergia(valor_energia);//seta o valor da energia do inimigo 

		}
		else if (linha.rfind("P: ", 0) == 0) {

			string parte_provisoes = linha.substr(3); //pega o numero da provisao 
			int valor_provisoes = stoi(parte_provisoes);// transforma o numero em int
			inimigo.setProvisoesDeixadas(valor_provisoes);//seta o valor da provisao do inimigo 

		}
		else if (linha.rfind("T: ", 0) == 0) {

			string parte_tesouro = linha.substr(3); //pega o numero da tesouro 
			int valor_tesouro = stoi(parte_tesouro);// transforma o numero em int
			inimigo.setTesouroDeixado(valor_tesouro);//seta o valor da tesouro do inimigo 
		}
		else if (linha.rfind("I: ", 0) == 0) {
			string dados_do_item = linha.substr(3);

			stringstream ss;
			ss.str(dados_do_item);
			string parte;

			string nome;
			char tipo = ' ';
			bool podeCombate = true;
			int fa = 0, dano = 0;

			getline(ss, parte, ';');
			nome = parte;

			getline(ss, parte, ';');
			if (!parte.empty()) tipo = parte[0];

			getline(ss, parte, ';');
			if (!parte.empty()) podeCombate = (stoi(parte) == 1);

			getline(ss, parte, ';');
			if (!parte.empty()) fa = stoi(parte);

			getline(ss, parte, ';');
			if (!parte.empty()) dano = stoi(parte);

			Item item_drop(nome, tipo, podeCombate, fa, dano);
			// Verifica se a cena já foi marcada como uma batalha
			if (ehBatalha) {
				// Se for uma batalha, o item é do inimigo e será pego após a vitória.
				inimigo.setItemDeixado(item_drop);
			}
			else {
				// Se NÃO for uma batalha, o item está na sala e é seu imediatamente.
				///jogador.adiciona_item(item_drop);
				itensEncontrados.push_back(item_drop); //// Guarda o item na lista da cena
			}
			///jogador.adiciona_item(item_drop);//adiciona o item dropado ao inventario //mas ja tem uma funcao q faz isso em iniciar batalha
			if (item_drop.get_nome() == "Sapo de Chocolate")
				jogador.adiciona_provisao(1);
		}
		
		 //Pergunta se O resultado da busca pelo caractere : na linha é diferente do valor de 'não encontrado'?
		else if (linha.find(':') != string::npos) {


			// Encontra a posicao do separador ':'
			size_t pos_colon = linha.find(':');

			// Pega a parte ANTES do ':' e converte para o ID da vitoria
			idCenaVitoria = stoi(linha.substr(0, pos_colon));

			// Pega a parte DEPOIS do ':' e converte para o ID da derrota
			idCenaDerrota = stoi(linha.substr(pos_colon + 1));
		}
		else if (linha == "TESTE_DE_SORTE") {
			ehUmTesteDeSorte = true;
		}
		else {
			if (!linha.empty()) { // se a linha que eu li não é nada de cima e não está vazia
				textoDaHistoria += linha + "\n"; // adiciono ao texto da história.
			}
		}
	} 

	arquivo.close();
	return true;

} 

int Cena::getIdCenaAtual() {
	return idCenaAtual;
}

bool Cena::ehUmaBatalha() {
	return ehBatalha;
}

string Cena::getTextoDaHistoria() {
	return textoDaHistoria;
}

map<int, string> Cena::getOpcoes() {
	return opcoes;
}

Inimigo& Cena::getInimigo(){
	return inimigo;
}

int Cena::getIdCenaDerrota() {
	return idCenaDerrota;
}

int Cena::getIdCenaVitoria() {
	return idCenaVitoria;
}

vector<Item> Cena::getItensEncontrados() {
	return itensEncontrados;
}

bool Cena::ehTesteDeSorte() {
	return ehUmTesteDeSorte;
}