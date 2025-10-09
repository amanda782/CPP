#include "jogo.h"
#include"Entidade.h"
#include"Jogador.h"
#include"Inimigo.h"
#include"Item.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream> // Essencial para o stringstream
#include <limits>  // Para o cin.ignore


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
		if (cena.carregarCena(idCenaAtual, jogador)) {
			cenasVisitadas.push_back(idCenaAtual); // Pegue o número da cena atual e adicione-o ao final da lista de cenas visitadas.
			salvarJogo();

				cout << "\n--- Cena " << idCenaAtual << " ---\n" << endl;
				cout << cena.getTextoDaHistoria() << endl;

				if (idCenaAtual == 9) {
					cout << "\nFIM DA AVENTURA! Obrigado por jogar." << endl;
					jogoRodando = false; // Sinaliza para o loop while terminar
				}


				else if (cena.ehUmaBatalha()) {
				iniciarBatalha();
				}

				else if (cena.ehTesteDeSorte()) {

				cout << "\nVoce se depara com um desafio e precisa testar sua sorte!" << endl;
				cout << "Pressione Enter para rolar os dados...";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();

				if (jogador.testar_sorte()) { // Chama o metodo do jogador que ja existe
					cout << "Sucesso! Voce superou o obstaculo." << endl;
					idCenaAtual = cena.getIdCenaVitoria(); // Pega o caminho do sucesso
				}
				else {
					cout << "Falha! Voce nao teve sorte desta vez." << endl;
					idCenaAtual = cena.getIdCenaDerrota(); // Pega o caminho da falha
					}
				}
				else {
				mostrarOpcoesEProcessarEscolha();
				}
			}
		}
	}



// Em jogo.cpp
void Jogo::iniciarBatalha() {
	Inimigo inimigo = cena.getInimigo();
	cout << "\n!!! BATALHA IMINENTE !!!" << endl;
	cout << "Voce encontrou um " << inimigo.getNome() << "!" << endl;
	cout << "------------------------------------------" << endl;

	// --- FASE DE PREPARAÇÃO ---
	bool iniciarCombate = false;
	while (!iniciarCombate) {
		
		cout << "--- PREPARACAO PARA O COMBATE ---" << endl;
		cout << "INIMIGO: " << inimigo.getNome() << " (Habilidade: " << inimigo.getHabilidade() << ", Energia: " << inimigo.getEnergia() << ")" << endl;
		cout << "VOCE   : " << jogador.getNome() << " (Energia: " << jogador.getEnergia() << "/" << jogador.getEnergiaMax() << ")" << endl;
		cout << "------------------------------------------" << endl;
		cout << "O que voce deseja fazer?" << endl;
		cout << "1. Gerenciar Inventario (Equipar Itens)" << endl;
		cout << "2. Usar Provisao (Recupera 4 de Energia)" << endl;
		cout << "3. Iniciar Combate" << endl;
		cout << "------------------------------------------" << endl;
		cout << "> ";

		int escolha;
		cin >> escolha;

		switch (escolha) {
		case 1:
			gerenciarInventario(); // Chama a função que criamos no Passo 1
			break;
		case 2:
			if (jogador.usar_provisao()) { // Tenta usar uma provisão
				cout << "\nVoce usou uma provisao! Sua energia foi restaurada." << endl;
			}
			else {
				cout << "\nVoce nao tem provisoes!" << endl;
			}
			cout << "Pressione Enter para continuar...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			break;
		case 3:
			iniciarCombate = true; // Sai do loop de preparação
			break;
		default:
			cout << "\nOpcao invalida! Tente novamente." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			break;
		}
	}

	// FASE DE COMBATE
	cout << "\nO combate comeca!" << endl;
	cout << "Pressione Enter para comecar o combate...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	while (jogador.estaVivo() && inimigo.estaVivo()) {
		
		cout << "--- NOVA RODADA ---" << endl;
		cout << "Energia do Inimigo: " << inimigo.getEnergia() << endl;
		cout << "Sua Energia: " << jogador.getEnergia() << endl;
		cout << "------------------------------------------" << endl;
		cout << "Pressione Enter para atacar...";
		cin.get();

		int fa_jogador = jogador.calcular_FA();
		int fa_inimigo = inimigo.calcular_FA();

		cout << "Sua Forca de Ataque: " << fa_jogador << endl;
		cout << "Forca de Ataque do Inimigo: " << fa_inimigo << endl;
		cout << "------------------------------------------" << endl;
		string answer_dano;

		if (fa_jogador > fa_inimigo) {
			int danoBase = jogador.getArmaEquipada().get_dano();
			if (danoBase <= 0) danoBase = 1; // Garante dano mínimo de 1

			cout << "Voce venceu a rodada e causou " << danoBase << " de dano!" << endl;
			cout << "Deseja testar a sorte para dobrar o dano? (sim/nao)" << endl;
			cin >> answer_dano;

			if (answer_dano == "sim")
				inimigo.receberDano(jogador.ampliar_dano(danoBase));
			else
				inimigo.receberDano(danoBase);
		}
		else if (fa_inimigo > fa_jogador) {
			cout << "O inimigo venceu a rodada e voce sofreu 2 de dano!" << endl;
			cout << "Deseja testar a sorte para reduzir o dano? (sim/nao)" << endl;
			cin >> answer_dano;

			if (answer_dano == "sim")
				jogador.receberDano(jogador.reduzir_dano(2));
			else
				jogador.receberDano(2);
		}
		else {
			cout << "Empate! Ninguem se feriu nesta rodada." << endl;
		}

		cout << "Pressione Enter para a proxima rodada...";
		cin.get();
	}

	// --- FASE PÓS-BATALHA
	system("cls");
	cout << "--- FIM DA BATALHA ---" << endl;
	if (jogador.estaVivo()) {
		cout << "Voce derrotou o " << inimigo.getNome() << "!" << endl << endl;
		// Coleta de recompensas
		int tesouro_ganho = inimigo.getTesouroDeixado();
		if (tesouro_ganho > 0) {
			cout << "Voce encontrou " << tesouro_ganho << " pecas de tesouro!" << endl;
			jogador.setTesouro(jogador.getTesouro() + tesouro_ganho);
		}

		int provisao_ganha = inimigo.getProvisoesDeixadas();
		if (provisao_ganha > 0) {
			cout << "Voce encontrou " << provisao_ganha << " provisao(oes)!" << endl;
			jogador.adiciona_provisao(provisao_ganha);
		}

		Item item_ganho = inimigo.getItemDeixado();
		if (item_ganho.get_nome() != "Item vazio") { // Verifica se é um item válido
			cout << "O inimigo deixou cair um item: " << item_ganho.get_nome() << endl;
			jogador.adiciona_item(item_ganho);
		}

		// Avança para a cena de vitória
		idCenaAtual = cena.getIdCenaVitoria();
	}
	else {
		cout << "Voce foi derrotado pelo " << inimigo.getNome() << "..." << endl;
		idCenaAtual = cena.getIdCenaDerrota();
	}
	cout << "\nPressione Enter para continuar sua jornada...";
	cin.get();
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
				arquivoDeSave 
					<< item.get_nome() << ";"
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


	bool Jogo::carregarJogo() {
		ifstream arquivoDeSave("save.txt");
		if (!arquivoDeSave.is_open()) {
			return false;
		}

		string linha;

		// --- LEITURA SEGURA DOS ATRIBUTOS ---
		// A logica agora e: TENTE ler uma linha, e SE conseguir E ela nao estiver vazia, converta.
		if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setHabilidade(stoi(linha));
		if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setEnergia(stoi(linha));
		if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setEnergiaMax(stoi(linha));
		if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setSorte(stoi(linha));
		if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setProvisoes(stoi(linha));
		if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setTesouro(stoi(linha));
		if (getline(arquivoDeSave, linha) && !linha.empty()) idCenaAtual = stoi(linha);

		// --- LEITURA SEGURA DAS CENAS VISITADAS ---
		if (getline(arquivoDeSave, linha) && !linha.empty()) {
			stringstream ss_cenas(linha);
			string parte_cena;
			cenasVisitadas.clear();
			while (getline(ss_cenas, parte_cena, ',')) {
				if (!parte_cena.empty()) {
					cenasVisitadas.push_back(stoi(parte_cena));
				}
			}
		}

		// --- LEITURA SEGURA DO INVENTARIO ---
		jogador.limparInventario();
		while (getline(arquivoDeSave, linha)) {
			if (linha.empty()) continue; // Pula linhas em branco no inventario

			stringstream ss_item(linha);
			string parte_item;
			string nome;
			char tipo;
			bool podeCombate;
			int fa, dano;

			getline(ss_item, parte_item, ';'); nome = parte_item;
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();

		return true;
	}

	void Jogo::criarNovoPersonagem() {

		system("cls");
		cout << "------------------------------------------" << endl;
		cout << "      CRIACAO DE PERSONAGEM" << endl;
		cout << "------------------------------------------" << endl << endl;

		// Mostra as regras e os pontos iniciais para o jogador
		cout << "Voce tem 12 pontos para distribuir entre seus atributos." << endl << endl;
		cout << "Seus atributos iniciais (valores minimos) sao:" << endl;
		// Pega os valores iniciais do objeto jogador, que foi criado com os minimos
		cout << "Habilidade: " << jogador.getHabilidade() << " (Max: 12)" << endl;
		cout << "Energia:    " << jogador.getEnergia() << " (Max: 24)" << endl;
		cout << "Sorte:      " << jogador.getSorte() << " (Max: 12)" << endl << endl;

		cout << "Pressione Enter para comecar a distribuir os pontos...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		system("cls");

		int pontos_disponiveis = 12;
		cout << "Vamos distribuir seus 12 pontos! " << endl << endl << endl;

		string escolha;
		int quantidade;
		int sobra; // armazena os pontos que podem ultrapassar o limite. 

		while(pontos_disponiveis >0) {

			cout <<"Voce tem " << pontos_disponiveis << " pontos disponiveis." << endl;
			cout << "Voce quer incrementar seus pontos em sorte, habilidade ou energia? " << endl << endl;
			cin >> escolha;
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); ///CONFIRMAR SE ISSO TÁ CERTO // julie

			cout << "Quantos pontos voce deseja incrementar? " << endl << endl;
			cin >> quantidade;

			// limpa o buffer de entrada para evitar erros na próxima leitura
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (quantidade <= 0 || quantidade > pontos_disponiveis) {
				cout << "Quantidade invalida. Tente novamente." << endl << endl;
				continue;
			}

			if (escolha == "sorte") 
				sobra = jogador.ajustarSorte(quantidade); // incrementa QUANTIDADE pontos em sorte

			else if (escolha == "habilidade") 
				sobra = jogador.ajustarHabilidade(quantidade); // incrementa QUANTIDADE pontos em habilidade
			
			else if (escolha == "energia") 
				sobra = jogador.ajustarEnergia(quantidade); // incrementa QUANTIDADE pontos em energia
			
			else {
				cout << "\nAtributo invalido! Tente novamente." << endl << endl;
				continue; // pula a dedução de pontos se a escolha foi inválida
			}

			// subtrai os pontos apenas se a escolha foi válida
			pontos_disponiveis -= quantidade;
			pontos_disponiveis += sobra; // adiciona os pontos que nao foram incrementados pois passaram do limite (pode ser zero)
		}
		jogador.setEnergiaMax(jogador.getEnergia()); // seta a energia atual como maxima

		cout << "\n--- Personagem Criado! ---" << endl;
		cout << "Habilidade Final: " << jogador.getHabilidade() << endl;
		cout << "Energia Final: " << jogador.getEnergia() << endl;
		cout << "Sorte Final: " << jogador.getSorte() << endl;
		cout << "------------------------------------------" << endl;
		cout << "Pressione Enter para comecar a aventura...";
		cin.get(); // pausa para o jogador ler os status antes do jogo começar
	}

	void Jogo::exibir_status_jogador() {
		cout << "\n--- STATUS FINAL DO PERSONAGEM ---" << endl;
		cout << "Habilidade: " << jogador.getHabilidade() << endl;
		cout << "Energia: " << jogador.getEnergia() << " / " << jogador.getEnergiaMax() << endl;
		cout << "Sorte: " << jogador.getSorte() << endl;
		cout << "------------------------------------" << endl;
	}


	void Jogo::gerenciarInventario() {
		system("cls");
		cout << "--- GERENCIAR INVENTARIO ---" << endl;

		// Mostra o status completo, incluindo itens já equipados
		jogador.imprime_inventario();

		vector<Item> inventario = jogador.get_inventario();

		if (inventario.empty()) {
			cout << "\nSua mochila esta vazia. Nao ha itens para equipar." << endl;
		}
		else {
			cout << "\n--- ITENS PARA EQUIPAR ---" << endl;
			for (int i = 0; i < inventario.size(); ++i) {
				cout << i << ". " << inventario[i].get_nome() << endl;
			}

			cout << "--------------------------" << endl;
			cout << "Digite o numero do item que deseja equipar (ou -1 para voltar): ";
			int escolha;
			cin >> escolha;

			if (cin.good() && escolha >= 0 && escolha < inventario.size()) {
				jogador.equipar_item(escolha); // chama a função para equipar
			}
			else if (escolha != -1) {
				cout << "Escolha invalida." << endl;
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}

		cout << "\nPressione Enter para voltar...";
		cin.get();
	}