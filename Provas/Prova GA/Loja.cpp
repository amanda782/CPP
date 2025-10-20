#include <string>
#include <iostream>
#include "Produto.h"
#include "Laptops.h"
#include "Smartphone.h"
#include "Tablet.h"
#include "Loja.h"

using namespace std;

Loja::Loja() {
	nome_loja = "LOJA VAZIA";
	tamanho_estoque = 0;

}
Loja::Loja(string nome) {
	nome_loja = nome;
	tamanho_estoque = 0;

}

Loja::~Loja(){}

void Loja::imprime_produto(int codigo) {
	for (int i = 0; i < tamanho_estoque; i++) {
		if (estoque[i]->get_codigo() == codigo) {
			estoque[i]->imprime_info();
			return;
		}
	}
	cout << "O produto nao foi encontrado em nosso estoque. " << endl;
	
}



void Loja::imprime_info_loja() {
	cout << "Nome da loja: " << nome_loja << endl;
	cout << "Quantidade de produtos: " << tamanho_estoque << endl << endl;

	if (tamanho_estoque > 0) {
		cout << endl << "Itens no estoque: " << endl;
		for (int i = 0; i < tamanho_estoque; i++) {
			estoque[i]->imprime_info();
			cout << endl;
		}
	}
}

void Loja::adicionar_ao_estoque(Produto* product) {
	bool produto_ja_existe = false;
	for (int i = 0; i < tamanho_estoque; i++) {
		if (estoque[i]->get_codigo() == product->get_codigo()) {
			cout << "Este produto ja existe no estoque: " << product->get_nome() << endl; // imprime o nome do produto que ja esta no estoque
			produto_ja_existe = true;
			break;
		}
	}
	if (!produto_ja_existe) {
		if (tamanho_estoque < 100) {
			estoque[tamanho_estoque] = product;
			tamanho_estoque++;
			cout << "Produto adicionado" << endl;

		}

	}
}


void Loja::remover_do_estoque(int codigo) {
	for (int i = 0; i <= tamanho_estoque; i++) {
		if (estoque[i]->get_codigo() == codigo) {
			//remove o estoque[i] do array
			for (i; i < tamanho_estoque - 1; ++i)
				estoque[i] = estoque[i + 1];
			tamanho_estoque--;
			cout << "Código do produto removido:" << codigo<< endl ; // imprime o nome do produto removido junto com o aviso
			return;
		}
	}
	cout << "Produto nao encontrado no estoque" << endl; // avisa que o produto nao estava no estoque, portanto nao foi removido
	
}

void Loja::valor_total() {
	float contador = 0;
	for (int i = 0; i < tamanho_estoque; i++) {
		contador += estoque[i]->get_preco();
	}
	cout << "Valor total do estoque: " << contador << endl;
}

int Loja::verifica_produto(Produto* z) {
	int contador = 0;
	for (int i = 0; i < tamanho_estoque; i++) {
		if (estoque[i]->get_codigo() == z->get_codigo())
			contador++; // verifica quantas vezes esse produto aparece no estoque
	}
	if (contador > 0)
		return contador;
	else {
		cout << "Produto não encontrado no estoque. " << endl;
		return 0;
	}
}

void Loja::aplicar_desconto(Produto* z, float porcentagem) {
	float novo_preco = z->get_preco() - (z->get_preco() * (porcentagem / 100));
	z->set_preco(novo_preco);
}

void Loja::verificar_acima(float preco) {
	Produto* nova_lista[100];
	int x = 0;
	for (int i = 0; i < tamanho_estoque; i++) {
		if (estoque[i]->get_preco() > preco) {
			nova_lista[x]=estoque[i];
			x++;
		}
	}

	if (x > 0) {
		cout << endl << "Foram encontrados " << x << " produtos com o valor maior que" << preco << " reais: " << endl << endl;
		for (int j = 0; j < x; j++) {
			nova_lista[j]->imprime_info();
		}
	
	}
	else
		cout << "Não foram encontrados produtos com o valor acima de " << preco << endl;

}


void Loja::editar_produto(Produto *x) {

	for (int i = 0; i < tamanho_estoque; i++) {
		if (estoque[i]->get_codigo() == x->get_codigo()) {
			cout << "Qual caracteristica do produto voce gostaria de editar: " << endl;
			cout << "1. Nome " << endl << "2. Preco " << endl;
			int resposta;
			

			if (Smartphone* smartphonePtr = dynamic_cast<Smartphone*>(x)) {

				cout << "3. Modelo " << endl << "4. Capacidade de armazenamento " << endl;
				cin >> resposta;
				if (resposta == 1) {
					string nome;
					cout << "Digite o novo nome do smartphone: " << endl;
					cin >> nome;
					smartphonePtr->set_nome(nome);
				}
				else if (resposta == 2) {
					float preco = 0;
					cout << "Digite o novo preco do smartphone: " << endl;
					cin >> preco;
					smartphonePtr->set_preco(preco);
				}
				else if (resposta == 3) {
					int modelo = 0;
					cout << "Digite o novo modelo do smartphone (int): " << endl;
					cin >> modelo;
					smartphonePtr->set_modelo(modelo);
				}

				else if (resposta == 4) {
					int capacidade = 0;
					cout << "Digite a nova capacidade de armazenamento do smartphone (int): " << endl;
					cin >> capacidade;
					smartphonePtr->set_armazenamento(capacidade);
				}


			}
			else if (Tablet* tabletPtr = dynamic_cast<Tablet*>(x)) {

				cout << "3. Marca " << endl << "4. Duracao da bateria " << endl;
				cin >> resposta;

				if (resposta == 1) {
					string nome;
					cout << "Digite o novo nome do tablet: " << endl;
					cin >> nome;
					tabletPtr->set_nome(nome);
				}
				else if (resposta == 2) {
					float preco = 0;
					cout << "Digite o novo preco do tablet: " << endl;
					cin >> preco;
					tabletPtr->set_preco(preco);
				}
				else if (resposta == 3) {
					string marca;
					cout << "Digite a nova marca do tablet: " << endl;
					cin >> marca;
					tabletPtr->set_marca(marca);
				}

				else if (resposta == 4) {
					float bateria = 0;
					cout << "Digite a nova duracao da bateria do tablet: " << endl;
					cin >> bateria;
					tabletPtr->set_bateria(bateria);
				}
			}

			else if (Laptops* laptopPtr = dynamic_cast<Laptops*>(x)) {

				cout << "3. Marca " << endl << "4. Tamanho da tela " << endl;
				cin >> resposta;

				if (resposta == 1) {
					string nome;
					cout << "Digite o novo nome do laptop: " << endl;
					cin >> nome;
					laptopPtr->set_nome(nome);
				}
				else if (resposta == 2) {
					float preco = 0;
					cout << "Digite o novo preco do laptop: " << endl;
					cin >> preco;
					laptopPtr->set_preco(preco);
				}
				else if (resposta == 3) {
					string marca;
					cout << "Digite a nova marca do laptop: " << endl;
					cin >> marca;
					laptopPtr->set_marca(marca);
				}

				else if (resposta == 4) {
					float tamanho = 0;
					cout << "Digite o novo tamanho da tela do laptop: " << endl;
					cin >> tamanho;
					laptopPtr->set_tamanho(tamanho);
				}
			}
		}
			
	}
}

void Loja::realizar_venda(Produto* z) {
	int quantidade = verifica_produto(z);
	if (quantidade > 0) {//realiza a venda
		remover_do_estoque(z->get_codigo()); // remove do estoque
	}
	cout << "Produto vendido: " << endl;
	z->imprime_info();
	cout << "Valor total da venda: " << z->get_preco() << endl << endl;
}

Produto* Loja::buscar_produto(int codigo) {
	for (int i = 0; i < tamanho_estoque; i++) {
		if (estoque[i]->get_codigo() == codigo) {
			return estoque[i]; // retorna o ponteiro do produto encontrado
		}
	}
	return nullptr; // retorna nulo se não encontrar
}