#include "Cabe�alho.h"

Biblioteca::Biblioteca() {
	ano = 0;
};
Biblioteca::Biblioteca(string t, string au, int a) {
	t�tulo = t;
	autor = au;
	ano = a;
};

Biblioteca::~Biblioteca() {}

void Biblioteca::imprime_infos() {
	cout << "T�tulo: " << t�tulo << endl;
	cout << "Autor: " << autor << endl;
	cout << "Ano: " << ano << endl;
};

void Biblioteca::idade_do_livro() {
	cout << "Idade do livro:" << 2025 - ano << endl;
}
