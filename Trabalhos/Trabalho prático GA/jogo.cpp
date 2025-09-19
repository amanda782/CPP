#include "jogo.h"
#include <fstream> 
#include <vector>


Jogo::Jogo() {
	idCenaAtual = 0;
	jogoRodando = false;
}

Jogo::~Jogo() {}

void Jogo::iniciarJogo() {
	idCenaAtual = 1;
	jogoRodando = true;
	while (jogoRodando == true) {
		cena.carregarCena(idCenaAtual); 
		if (cena.ehUmaBatalha() == true) {
			//iniciarBatalha(); //método ainda não foi criado
		}else (cena.ehUmaBatalha == false)
			// escolha() // tb não foi criado
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
					iniciarJogo();    // 2. Se conseguiu, começa o jantar.
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
			arquivoDeSave << jogador.getProvisoes() << endl;
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
			vector<Item> inventario = jogador.getInventario();
			for (auto item : inventario) {
				// Escreve cada item no formato: nome;tipo;combate;fa;dano
				arquivoDeSave << item.getNome() << ";"
					<< item.getTipoDeItem() << ";"
					<< item.getPodeEmCombate() << ";"
					<< item.getFa() << ";"
					<< item.getDano() << endl;
			}

			// 6. Fecha o arquivo para garantir que tudo foi salvo
			arquivoDeSave.close();
		}
		else {
			cout << "ERRO: Nao foi possivel criar o arquivo de salvamento." << endl;
		}
	}
