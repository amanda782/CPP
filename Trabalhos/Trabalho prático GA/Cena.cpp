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

bool Cena::carregarCena(int numeroDaCena) {

	textoDaHistoria = "";
	opcoes.clear(); // O metodo .clear() esvazia um map
	itensEncontrados.clear(); // e tambem um vector
	ehBatalha = false;
	idCenaVitoria = 0;
	idCenaDerrota = 0;

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
		if (linha.rfind("#", 0) == 0) { // o r.find acha algo na linha, nesse caso é # e ele inicia a busca no caracter 0. o == é para referenciar que ele achou NO CARACTERE 0.
			// size_t é um tipo de variável, ele armazena só numeros positivos e grandes.
			size_t coloca_dois_pontos = linha.find(':'); //procura a posição dos : e retorna o num de posição deles

			string parte_numero = linha.substr(1, coloca_dois_pontos - 1); // essa função aqui corta a linha/string. ele inicia na posição 1, já que a 0 sabemos que é # mesmo. depois, ele pega a posição dos dois pontos -1, porque sabe que o numero da cena está entre # e :.
			int id_proxima_cena = stoi(parte_numero); //stoi converte string p numero int. logo, ele converte o numero de cena encontrado acima em um int

			string parte_texto = linha.substr(coloca_dois_pontos + 2);// quer pegar onde inicia o texto da escolha, então ele localiza os : e pula 2 caracteres ( o próprio : e espaço)

			opcoes[id_proxima_cena] = parte_texto; // aqui a gente coloca o numero encontrado no texto e o texto que encontramos associados apartir da função map, em opções.
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

			// Usa um stringstream para facilitar a "quebra" da string
			stringstream ss;
			ss.str(dados_do_item); //coloca dados do item dentro do stringstream, que com o getline, pode ser qeubrado
			string parte;

			// Variaveis para guardar os 5 atributos do item
			string nome;
			char tipo;
			bool podeCombate;
			int fa, dano;

			//o getline não funciona com string normal, só stringstream.

			getline(ss, parte, ';'); nome = parte; //Le de ss, guarda em 'parte', e para no primeiro ';' que encontrar.
			getline(ss, parte, ';'); tipo = parte[0]; // Pega o primeiro caractere
			getline(ss, parte, ';'); podeCombate = (stoi(parte) == 1);
			getline(ss, parte, ';'); fa = stoi(parte);//stoi transforma a string em int 
			getline(ss, parte, ';'); dano = stoi(parte);

			// Cria um objeto Item com os dados lidos
			Item item_drop(nome, tipo, podeCombate, fa, dano);
			inimigo.setItemDeixado(item_drop);
		}
		// Pergunta se O resultado da busca pelo caractere : na linha é diferente do valor de 'não encontrado'?
		else if (linha.find(':') != string::npos) {

			// Encontra a posicao do separador ':'
			size_t pos_colon = linha.find(':');

			// Pega a parte ANTES do ':' e converte para o ID da vitoria
			idCenaVitoria = stoi(linha.substr(0, pos_colon));

			// Pega a parte DEPOIS do ':' e converte para o ID da derrota
			idCenaDerrota = stoi(linha.substr(pos_colon + 1));
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
	return cenaAtual;
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

Inimigo Cena::getInimigo(){
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
