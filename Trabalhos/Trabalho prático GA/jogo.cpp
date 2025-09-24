#include "jogo.h"
#include"Entidade.h"
#include"Jogador.h"
#include"Inimigo.h"
#include"Item.h"
#include <iostream>
#include <fstream> 
#include <vector>

using namespace std;


Jogo::Jogo() {
	idCenaAtual = 0;
	jogoRodando = false;
}

Jogo::~Jogo() {}

void Jogo::iniciarJogo() {
	idCenaAtual = 1;
	jogoRodando = true;
	mostrarTelaDeAbertura();

	while (jogoRodando == true) {
		cena.carregarCena(idCenaAtual);

		cout << "\n--- Cena " << idCenaAtual << " ---\n" << endl;
		cout << cena.getTextoDaHistoria() << endl;

		if (cena.ehUmaBatalha()) {
			iniciarBatalha();
		}
		else {
			mostrarOpcoesEProcessarEscolha();
		}
	}
}


void Jogo::mostrarOpcoesEProcessarEscolha() {
	map<int, string> opcoes = cena.getOpcoes();
	cout << "\nO que voce faz?" << endl;
	cout << "------------------------------------------" << endl;

  // Este loop 'for' percorre o mapa e imprime cada par de ID e Texto.
	for (auto escolha : opcoes) { //TIRAR DUVIDA COM O SOR 
		cout << escolha.first << ". " << escolha.second << endl; // .first acessa o número e .second acessa o texto do map 
	}
	cout << "------------------------------------------" << endl;

	cout << "> ";
	int escolha;
	cin >> escolha;

	idCenaAtual = escolha;
}
 

void Jogo::mostrarTelaDeCreditos() {
	// Comando para limpar a tela do console (cls para Windows, clear para Linux/macOS)
	system("cls");

	cout << "------------------------------------------" << endl;
	cout << "          CRÉDITOS DO JOGO" << endl;
	cout << "------------------------------------------" << endl << endl;

	// O trabalho pede para apresentar os nomes dos programadores 
	cout << "Desenvolvido por:" << endl;
	cout << "Julie Donatti Feck" << endl;
	cout << "Amanda Mirela Dienstmann" << endl << endl;

	cout << "------------------------------------------" << endl;
	cout << "\nPressione Enter para voltar ao menu...";

	// Limpa qualquer entrada de teclado anterior que possa ter sobrado
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // esse cin.ignore limpa o que tá no teclado, e o que tá dentro dos parenteses diz que não importa o tamanho do que estiver lá dentro, é pra limpar

	// Pausa o programa e espera o usuario pressionar a tecla Enter
	cin.get(); // depois desse enter volta para o menu (tela de abertura)
}

void Jogo::mostrarTelaDeAbertura() {
	bool sairDoMenu = false;
	while (!sairDoMenu) {
		// Limpa a tela para o menu aparecer limpo a cada volta
		system("cls");

		cout << "------------------------------------------" << endl;
		cout << "        AVENTURAS EM HOGWARTS" << endl;
		cout << "------------------------------------------" << endl << endl;

		cout << "1. Novo Jogo" << endl;
		cout << "2. Carregar Jogo" << endl;
		cout << "3. Creditos" << endl;
		cout << "4. Sair" << endl << endl;
		cout << "------------------------------------------" << endl;

		cout << "Escolha uma opcao: ";
		int escolha;
		cin >> escolha;

		switch (escolha) {
		case 1:
			criarNovoPersonagem();
			sairDoMenu = true;
			break;

		case 2:
			//iniciarJogo();
			//sairDoMenu = true; //ISSO FOI O QUE FIZ, TÁ ERRADO, PORQUE NÃO É SÓ INICIAR, É CARREGAR ALGO QUE JÁ EXISTE.
			//break; 

			if (carregarJogo()) { // 1. Tenta arrumar a mesa com os dados do save.
				sairDoMenu = true;
			}
			else {
				// Avisa que nao conseguiu arrumar a mesa (nao achou o save).
				cout << "Nenhum jogo salvo encontrado." << endl;
			}
			break;

		case 3:
			mostrarTelaDeCreditos();
			//NÃO PRECISA DE SAIRDOMENU PORQUE A INTENÇÃO É QUE O JOGADOR VOLTE PARA O MENU DENTRO DA PRÓPRIA FUNÇÃO. 
			break;

		case 4:
			cout << "Ate a proxima!" << endl;
			jogoRodando = false;  // Desliga o loop principal do jogo
			sairDoMenu = true;    // E tambem sai do loop do menu
			break;

		default: // Caso o jogador digite um numero invalido
			cout << "Opcao invalida! Pressione Enter para tentar novamente...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			break;

		}

	}
}

	void Jogo::salvarJogo() {
		// 1. Abre (ou cria) um arquivo chamado "save.txt" para escrita.
		// O ofstream apaga o conteudo anterior do arquivo, o que e perfeito para o auto-save.
		ofstream arquivoDeSave("save.txt");

		// 2. Verifica se o arquivo pôde ser aberto
		if (arquivoDeSave.is_open()) {

			// 3. Salva os dados do personagem, um por linha
			//arquivoDeSave << jogador.getNome() << endl; // O nome nao e necessario se for sempre Harry
			arquivoDeSave << jogador.getHabilidade() << endl;
			arquivoDeSave << jogador.getEnergia() << endl;
			arquivoDeSave << jogador.getEnergiaMax() << endl;
			arquivoDeSave << jogador.getSorte() << endl;
			arquivoDeSave << jogador.get_provisoes_atuais() << endl;
			arquivoDeSave << jogador.getTesouro() << endl;

			//Salva o estado do jogo
			arquivoDeSave << idCenaAtual << endl;
			//arquivoDeSave é um objeto de ofstream, que tratamos como cout e por isso colocamos com << as coisa dentro dele (que é um arquivo tb)

			// Salva as cenas visitadas, separadas por virgula (ex: "1,4,5,")
			for (int id : cenasVisitadas) { //Para cada int (que vamos chamar de id) dentro da lista cenasVisitadas, faça o seguinte. "Eu quero que você pegue cada lápis de dentro da caixa cenasVisitadas, um de cada vez, do primeiro ao último.""A cada volta, o lápis que você pegar da caixa, guarde-o temporariamente em uma nova variável do tipo int chamada id."
				arquivoDeSave << id << ",";
			}
			arquivoDeSave << endl; // pula linha depois do for 

			// 5. Salva o inventario completo, um item por linha
			vector<Item> inventario = jogador.get_inventario();
			for (auto item : inventario) {
				// Escreve cada item no formato: nome;tipo;combate;fa;dano
				arquivoDeSave << item.get_nome() << ";"
					<< item.get_tipo() << ";"
					<< item.get_combate() << ";"
					<< item.get_FA() << ";"
					<< item.get_dano() << endl;
			}

			// 6. Fecha o arquivo para garantir que tudo foi salvo
			arquivoDeSave.close();
		}
		else {
			cout << "ERRO: Nao foi possivel criar o arquivo de salvamento." << endl;
		}
	}
#include <fstream>
#include <sstream> // Essencial para o stringstream
#include <iostream>
#include <limits>  // Para o cin.ignore

	bool Jogo::carregarJogo() {
		//  Tenta abrir o arquivo "save.txt" para leitura
		ifstream arquivoDeSave("save.txt");
				// Se nao conseguiu abrir (ex: o arquivo nao existe), avisa que falhou e retorna.
		if (!arquivoDeSave.is_open()) {
			return false;
		}

		// Variavel temporaria para ler cada linha
		string linha;

		getline(arquivoDeSave, linha); jogador.setHabilidade(stoi(linha));
		getline(arquivoDeSave, linha); jogador.setEnergia(stoi(linha));
		getline(arquivoDeSave, linha); jogador.setEnergiaMax(stoi(linha));
		getline(arquivoDeSave, linha); jogador.setSorte(stoi(linha));
		getline(arquivoDeSave, linha); jogador.setProvisoes(stoi(linha));
		getline(arquivoDeSave, linha); jogador.setTesouro(stoi(linha));

		// Le e define a cena onde o jogo deve continuar
		getline(arquivoDeSave, linha); idCenaAtual = stoi(linha);

		getline(arquivoDeSave, linha); // Le a linha inteira (ex: "1,4,5,")

		stringstream ss_cenas(linha); // Usa um stringstream para quebrar a linha
		string parte_cena;
		cenasVisitadas.clear(); // Limpa o vetor de cenas visitadas antes de preencher

		// Loop que le cada numero separado por virgula
		while (getline(ss_cenas, parte_cena, ',')) {
			if (!parte_cena.empty()) { // Garante que nao pegamos partes vazias
				cenasVisitadas.push_back(stoi(parte_cena));
			}
		}

		jogador.limparInventario(); // Esvazia o inventario atual antes de adicionar os itens salvos

		// Loop que le o resto do arquivo, linha por linha. Cada linha e um item.
		while (getline(arquivoDeSave, linha)) {
			stringstream ss_item(linha);
			string parte_item;

			// Variaveis para guardar os 5 atributos do item
			string nome;
			char tipo;
			bool podeCombate;
			int fa, dano;

			// Pega as partes separadas por ';'
			getline(ss_item, parte_item, ';'); nome = parte_item;  // lê o que tá em ss_item ATÉ O ; e coloca em parte_item 
			getline(ss_item, parte_item, ';'); tipo = parte_item[0];
			getline(ss_item, parte_item, ';'); podeCombate = (stoi(parte_item) == 1);
			getline(ss_item, parte_item, ';'); fa = stoi(parte_item);
			getline(ss_item, parte_item, ';'); dano = stoi(parte_item);

			Item itemCarregado(nome, tipo, podeCombate, fa, dano);
			jogador.adiciona_item(itemCarregado);
		}

		arquivoDeSave.close();

		cout << "\nJogo carregado com sucesso!" << endl;
		cout << "Pressione Enter para continuar...";
		// cin.ignore para limpar qualquer entrada residual antes de pausar
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();

		return true; // Retorna 'true' para indicar que o carregamento foi um sucesso
	}

	void Jogo::criarNovoPersonagem() {
		int pontos_disponiveis = 12;
		cout << "Vamos distribuir seus 12 pontos! " << endl;

		string escolha;
		int quantidade;
		int contador;
		int sobra; // armazena os pontos que podem ultrapassar o limite. 

		while(pontos_disponiveis >0) {

			cout <<"Você tem" << pontos_disponiveis << "pontos disponíveis." << endl;
			cout << "Você quer incrementar seus pontos em sorte, habilidade ou energia? " << endl;
			cin >> escolha;

			cout << "Quantos pontos voce deseja incrementar? " << endl;
			cin >> quantidade;

			if (quantidade > pontos_disponiveis) {
				cout << "Voce nao tem essa quantidade de pontos disponiveis. Tente novamente. " << endl;
				continue;
			}

			if (escolha == "sorte") 
				sobra = jogador.ajustarSorte(quantidade); // incrementa QUANTIDADE pontos em sorte

			if (escolha == "habilidade") 
				sobra = jogador.ajustarHabilidade(quantidade); // incrementa QUANTIDADE pontos em habilidade
			
			else if (escolha == "energia") 
				sobra = jogador.ajustarEnergia(quantidade); // incrementa QUANTIDADE pontos em energia
			
			else {
				cout << "\nAtributo invalido! Tente novamente." << endl;
				continue; // pula a dedução de pontos se a escolha foi inválida
			}

			// subtrai os pontos apenas se a escolha foi válida
			pontos_disponiveis -= quantidade;
			pontos_disponiveis += sobra; // adiciona os pontos que nao foram incrementados pois passaram do limite (pode ser zero)
		}
		cout << "\n--- Personagem Criado! ---" << endl;
		cout << "Habilidade Final: " << jogador.getHabilidade() << endl;
		cout << "Energia Final: " << jogador.getEnergia() << endl;
		cout << "Sorte Final: " << jogador.getSorte() << endl;
		cout << "------------------------------------------" << endl;
	}