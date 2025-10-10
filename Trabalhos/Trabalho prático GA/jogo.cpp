#include "jogo.h"
#include "Entidade.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "Item.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include <limits>

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
			cenasVisitadas.push_back(idCenaAtual);
			salvarJogo();

			cout << "\n--- Cena " << idCenaAtual << " ---\n" << endl;
			cout << cena.getTextoDaHistoria() << endl;

			vector<Item> itensDaCena = cena.getItensEncontrados();
			if (!itensDaCena.empty()) {
				cout << "------------------------------------------" << endl;
				for (size_t i = 0; i < itensDaCena.size(); ++i) {
					Item& item = itensDaCena[i];
					jogador.adiciona_item(item);
					cout << "Voce adicionou o item " << item.get_nome() << " ao seu inventario!" << endl;
				}
			}

			if (idCenaAtual == 7) {
				cout << "\nFIM DA AVENTURA! Obrigado por jogar." << endl;
				jogoRodando = false;
			}
			else if (cena.ehUmaBatalha()) {
				iniciarBatalha();
			}
			else if (cena.ehTesteDeSorte()) {
				cout << "\nVoce se depara com um desafio e precisa testar sua sorte!" << endl;
				cout << "Pressione Enter para rolar os dados...";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();

				if (jogador.testar_sorte()) {
					cout << "Sucesso! Voce superou o obstaculo." << endl;
					idCenaAtual = cena.getIdCenaVitoria();
				}
				else {
					cout << "Falha! Voce nao teve sorte desta vez." << endl;
					idCenaAtual = cena.getIdCenaDerrota();
				}
			}
			else {
				mostrarOpcoesEProcessarEscolha();
			}
		}
		else { // Adicionado para o caso de carregarCena retornar false (ex: cena 0)
			jogoRodando = false;
		}

	}
	cout << "\nFIM DA AVENTURA! Obrigado por jogar." << endl;
	mostrarTelaDeCreditos();
}

void Jogo::iniciarBatalha() {
	Inimigo& inimigo = cena.getInimigo();
	cout << "\n!!! BATALHA IMINENTE !!!" << endl;
	cout << "Voce encontrou um " << inimigo.getNome() << "!" << endl;
	cout << "------------------------------------------" << endl;

	bool iniciarCombate = false;
	while (!iniciarCombate) {
		cout << "--- PREPARACAO PARA O COMBATE ---" << endl;
		cout << "INIMIGO: " << inimigo.getNome() << " (Habilidade: " << inimigo.getHabilidade() << ", Energia: " << inimigo.getEnergia() << ")" << endl;
		cout << "VOCE   : " << jogador.getNome() << " (Habilidade:" << jogador.getHabilidade() << ", Energia: " << jogador.getEnergia() << ")" << endl;
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
			gerenciarInventario();
			break;
		case 2:
			if (jogador.usar_provisao()) {
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
			iniciarCombate = true;
			break;
		default:
			cout << "\nOpcao invalida! Tente novamente." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			break;
		}
	}

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
			if (danoBase <= 0) danoBase = 1;

			cout << "Voce venceu a rodada e causou " << danoBase << " de dano!" << endl;
			cout << "Deseja testar a sorte para dobrar o dano? (sim/nao)" << endl;
			cin >> answer_dano;

			if (answer_dano == "sim")
				inimigo.receberDano(jogador.ampliar_dano(danoBase));
			else
				inimigo.receberDano(danoBase);
		}
	
		else if (fa_inimigo > fa_jogador) {
			//  Pega o item do inimigo para saber o dano base dele
			Item armaInimigo = inimigo.getItemDeixado();
			int danoInimigo = armaInimigo.get_dano();

			//  Se o inimigo não tiver um item (dano 0), o dano padrão dele é 2
			if (danoInimigo <= 0) {
				danoInimigo = 2;
			}

			// Pega a sua armadura equipada
			Item armadura_equipada = jogador.getArmaduraEquipada();
			int reducao = armadura_equipada.get_dano(); // Se não tiver armadura, será 0 (corrigimos no Passo 1)

			// CALCULA O DANO FINAL DA FORMA CORRETA E SEGURA
			int dano_final = danoInimigo - abs(reducao); // modulo de reducao

			if (dano_final < 0) {
				dano_final = 0;
			}

			cout << "O inimigo venceu a rodada e voce sofreu " << dano_final << " de dano!" << endl;
			cout << "Deseja testar a sorte para reduzir o dano? (sim/nao)" << endl;
			string answer_dano;
			cin >> answer_dano;

			if (answer_dano == "sim") {
				jogador.receberDano(jogador.reduzir_dano(dano_final));
			}
			else {
				jogador.receberDano(dano_final);
				jogador.foiSalvoPelaPedra();
			}
		}
		
		else {
			cout << "Empate! Ninguem se feriu nesta rodada." << endl;
		}

		cout << "Pressione Enter para a proxima rodada..." << endl;
		cin.get();
	} 

	system("cls");
	cout << "--- FIM DA BATALHA ---" << endl;
	if (jogador.estaVivo()) {
		cout << "Voce derrotou o " << inimigo.getNome() << "!" << endl << endl;

		int tesouro_ganho = inimigo.getTesouroDeixado();
		if (tesouro_ganho > 0) {
			cout << "Voce encontrou " << tesouro_ganho << " galeoes!" << endl;
			jogador.setTesouro(jogador.getTesouro() + tesouro_ganho);
		}

		int provisao_ganha = inimigo.getProvisoesDeixadas();
		if (provisao_ganha > 0) {
			cout << "Voce encontrou " << provisao_ganha << " provisao(oes)!" << endl;
			jogador.adiciona_provisao(provisao_ganha);
		}

		Item item_ganho = inimigo.getItemDeixado();
		if (item_ganho.get_nome() != "Item vazio") {
			cout << "O inimigo deixou cair um item: " << item_ganho.get_nome() << endl;
			jogador.adiciona_item(item_ganho);
		}

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
	cout << "\n------------------------------------------" << endl;
	cout << "O que voce faz?" << endl;

	for (map<int, string>::iterator it = opcoes.begin(); it != opcoes.end(); ++it) {
		cout << it->first << ". " << it->second << endl;
	}
	cout << "------------------------------------------" << endl;

	cout << "> ";
	int escolha;
	cin >> escolha;

	idCenaAtual = escolha;
}

void Jogo::mostrarTelaDeCreditos() {
	system("cls");
	cout << "------------------------------------------" << endl;
	cout << "          CRÉDITOS DO JOGO" << endl;
	cout << "------------------------------------------" << endl << endl;
	cout << "Desenvolvido por:" << endl;
	cout << "Julie Donatti Feck" << endl;
	cout << "Amanda Mirela Dienstmann" << endl << endl;
	cout << "------------------------------------------" << endl;
	cout << "\nPressione Enter para voltar ao menu...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

void Jogo::mostrarTelaDeAbertura() {
	bool sairDoMenu = false;
	while (!sairDoMenu) {
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
			if (carregarJogo()) {
				sairDoMenu = true;
			}
			else {
				cout << "Nenhum jogo salvo encontrado." << endl;
				cout << "Pressione Enter para continuar...";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
			}
			break;
		case 3:
			mostrarTelaDeCreditos();
			break;
		case 4:
			cout << "Ate a proxima!" << endl;
			jogoRodando = false;
			sairDoMenu = true;
			break;
		default:
			cout << "Opcao invalida! Pressione Enter para tentar novamente...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			break;
		}
	}
}

void Jogo::salvarJogo() {
	ofstream arquivoDeSave("save.txt");
	if (arquivoDeSave.is_open()) {
		arquivoDeSave << jogador.getHabilidade() << endl;
		arquivoDeSave << jogador.getEnergia() << endl;
		arquivoDeSave << jogador.getEnergiaMax() << endl;
		arquivoDeSave << jogador.getSorte() << endl;
		arquivoDeSave << jogador.get_provisoes_atuais() << endl;
		arquivoDeSave << jogador.getTesouro() << endl;
		arquivoDeSave << idCenaAtual << endl;

		for (size_t i = 0; i < cenasVisitadas.size(); ++i) {
			arquivoDeSave << cenasVisitadas[i] << ",";
		}
		arquivoDeSave << endl;

		vector<Item> inventario = jogador.get_inventario();
		for (size_t i = 0; i < inventario.size(); ++i) {
			Item& item = inventario[i];
			arquivoDeSave
				<< item.get_nome() << ";"
				<< item.get_tipo() << ";"
				<< item.get_combate() << ";"
				<< item.get_FA() << ";"
				<< item.get_dano() << endl;
		}
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

	if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setHabilidade(stoi(linha));
	if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setEnergia(stoi(linha));
	if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setEnergiaMax(stoi(linha));
	if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setSorte(stoi(linha));
	if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setProvisoes(stoi(linha));
	if (getline(arquivoDeSave, linha) && !linha.empty()) jogador.setTesouro(stoi(linha));
	if (getline(arquivoDeSave, linha) && !linha.empty()) idCenaAtual = stoi(linha);

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

	jogador.limparInventario();
	while (getline(arquivoDeSave, linha)) {
		if (linha.empty()) continue;

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
	cout << "Voce tem 12 pontos para distribuir entre seus atributos." << endl << endl;
	cout << "Seus atributos iniciais (valores minimos) sao:" << endl;
	cout << "Habilidade: " << jogador.getHabilidade() << " (Max: 12)" << endl;
	cout << "Energia:    " << jogador.getEnergia() << " (Max: 24)" << endl;
	cout << "Sorte:      " << jogador.getSorte() << " (Max: 12)" << endl << endl;
	cout << "Pressione Enter para comecar a distribuir os pontos...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();

	int pontos_disponiveis = 12;
	cout << "Vamos distribuir seus 12 pontos! " << endl << endl << endl;

	string escolha;
	int quantidade;
	int sobra;

	while (pontos_disponiveis > 0) {
		cout << "Voce tem " << pontos_disponiveis << " pontos disponiveis." << endl;
		cout << "Voce quer incrementar seus pontos em sorte, habilidade ou energia? " << endl << endl;
		cin >> escolha;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Quantos pontos voce deseja incrementar? " << endl << endl;
		cin >> quantidade;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (quantidade <= 0 || quantidade > pontos_disponiveis) {
			cout << "Quantidade invalida. Tente novamente." << endl << endl;
			continue;
		}

		if (escolha == "sorte")
			sobra = jogador.ajustarSorte(quantidade);
		else if (escolha == "habilidade")
			sobra = jogador.ajustarHabilidade(quantidade);
		else if (escolha == "energia")
			sobra = jogador.ajustarEnergia(quantidade);
		else {
			cout << "\nAtributo invalido! Tente novamente." << endl << endl;
			continue;
		}

		pontos_disponiveis -= quantidade;
		pontos_disponiveis += sobra;
	}
	jogador.setEnergiaMax(jogador.getEnergia());

	cout << "\n--- Personagem Criado! ---" << endl;
	cout << "Habilidade Final: " << jogador.getHabilidade() << endl;
	cout << "Energia Final: " << jogador.getEnergia() << endl;
	cout << "Sorte Final: " << jogador.getSorte() << endl;
	cout << "------------------------------------------" << endl;
	cout << "Pressione Enter para continuar...";
	cin.get();

	cout << "\nVoce recebe seus equipamentos iniciais!" << endl;
	Item varinhaInicial("Varinha", 'w', true, 1, 2);
	jogador.adiciona_item(varinhaInicial); // Adiciona a varinha na mochila
	jogador.equipar_item(0);               // Equipa o primeiro item da mochila (a varinha)

	cout << "Pressione Enter para comecar a aventura...";
	cin.get();
}

void Jogo::exibir_status_jogador() {
	cout << "\n--- STATUS FINAL DO PERSONAGEM ---" << endl;
	cout << "Habilidade: " << jogador.getHabilidade() << endl;
	cout << "Energia: " << jogador.getEnergia() << " / " << jogador.getEnergiaMax() << endl;
	cout << "Sorte: " << jogador.getSorte() << endl;
	cout << "------------------------------------" << endl;
}

// Em jogo.cpp
void Jogo::gerenciarInventario() {
	system("cls");
	cout << "--- GERENCIAR INVENTARIO ---" << endl;

	// Mostra o status completo, incluindo itens já equipados
	jogador.imprime_inventario();

	vector<Item> inventario = jogador.get_inventario();
	if (inventario.empty()) {
		cout << "\nSua mochila esta vazia." << endl;
	}
	else { // filtra itens equipaveis
	
		// cria uma lista temporária para guardar a POSIÇÃO dos itens equipáveis
		vector<int> indices_equipaveis;
		for (int i = 0; i < inventario.size(); ++i) {
			// Verifica se o item é uma arma ('w') ou armadura ('a')
			if (inventario[i].get_tipo() == 'w' || inventario[i].get_tipo() == 'a') {
				indices_equipaveis.push_back(i); // guarda o índice original do item
			}
		}

		// verifica se algum item equipável foi encontrado
		if (indices_equipaveis.empty()) {
			cout << "\nNao ha itens equipaveis na sua mochila." << endl;
		}
		else {
			cout << "\n--- ITENS PARA EQUIPAR ---" << endl;
			// Mostra o menu apenas com os itens filtrados
			for (int i = 0; i < indices_equipaveis.size(); ++i) {
				int indice_real = indices_equipaveis[i]; // Pega o índice original
				cout << i + 1 << ". " << inventario[indice_real].get_nome() << endl;
			}

			cout << "--------------------------" << endl;
			cout << "Digite o numero do item que deseja equipar (ou -1 para voltar): ";
			int escolha;
			cin >> escolha;

			// Converte a escolha do menu para o índice real do inventário
			if (cin.good() && escolha > 0 && escolha <= indices_equipaveis.size()) {
				int indice_real_para_equipar = indices_equipaveis[escolha - 1];
				jogador.equipar_item(indice_real_para_equipar);
			}
			else if (escolha != -1) {
				cout << "Escolha invalida." << endl;
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	cout << "\nPressione Enter para voltar...";
	cin.get();
}

