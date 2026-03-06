#include <iostream>
#include <string>
#include "ListaOrdenada.h" 
#include <cstdlib>
#include <ctime>

using namespace std;

struct Combatente {
    int nome;
    int iniciativa;

    // construtor pra facilitar a vida
    Combatente(int n, int i) {
        nome = n;
        iniciativa = i;
    }

    // construtor vazio (necessario pq o template cria T() as vezes)
    Combatente() {
        nome = 0;
        iniciativa = 0;
    }

    // A MAGICA ACONTECE AQUI
    // estamos ensinando pro c++ como comparar dois combatentes
    // a lista vai usar isso pra ordenar sozinho
    bool operator<(const Combatente& outro) const {
        // logica: quem tem iniciativa MENOR ou IGUAL vai ficando pra tras
        // o <= garante que se for igual, o novo continua andando e fica DEPOIS (criterio de desempate)
        return this->iniciativa <= outro.iniciativa;
    }

    // logica pra comparar igualdade (pro metodo remove/find)
    bool operator==(const Combatente& outro) const {
        return this->nome == outro.nome; // nome é o id unico
    }

    // logica pro 'cout << combatente' funcionar direto
    friend ostream& operator<<(ostream& os, const Combatente& c) {
        os <<"Nome: "<< c.nome << " Iniciativa: " << c.iniciativa << endl;
        return os;
    }

    // logica pro 'cout' com o ponteiro (se a lista usar ponteiro pro dado)
    bool operator>(const Combatente& outro) const {
        return this->iniciativa > outro.iniciativa;
    }
};
int main() {
	srand(time(0));
    ListaOrdenada<Combatente> l1;

	for (int i = 0; i < 10; i++) {
        int n = (rand() % 10) + 1;
        Combatente c(i, n) ;
        l1.insert(c);

	}
    l1.print();

	int lavador = (rand() % 5) + 1; // vai de 1 a 5
    return 0;
}
