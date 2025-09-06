#include "Nadador.h"
#include "Competicao.h"
#include "Data.h"
#include "Atleta.h"

Nadador::Nadador(string nome, int idade, string cat) : Atleta(nome, idade) { //inicializa o nadador e o atleta
    categoria = cat;
} 

void Nadador::imprime_info() {
    Atleta::imprime_info(); // imprime nome e idade do atleta
    cout << "Categoria: " << categoria << endl; // puxa o atributo pra imprimir

}

string Nadador::get_categoria() {
    return categoria;
}