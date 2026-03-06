#include "InformacoesAtleta.h"
#include "Nadador.h"
#include "Corredor.h"



void InformacoesAtleta::imprime_exclusivos_atleta(Atleta* atleta)) {
    // Tenta escanear o crachá "ATLETA" e ver se é de um NADADOR.
   // A linha abaixo faz 3 coisas:
   // 1. Tenta o dynamic_cast.
   // 2. Se funcionar, cria um ponteiro temporário 'n' do tipo Nadador*.
   // 3. O 'if' verifica se 'n' não é nulo (se o cast deu certo).

   if (Nadador* n = dynamic_cast<Nadador*>(atleta)) {
       // SUCESSO! O scanner nos deu um crachá de Nadador. Agora podemos usar 'n'.
       cout << "É um nadador, e sua categoria é: " << n->get_categoria() << endl;
   }
   // Se o primeiro 'if' falhou, vamos tentar escanear para CORREDOR.
   else if (Corredor* c = dynamic_cast<Corredor*>(atleta)) {
       // SUCESSO! O scanner nos deu um crachá de Corredor. Agora podemos usar 'c'.
       cout << "É um corredor, e o peso deste corredor é: " << c->get_peso() << endl;
   }
}
void InformacoesAtleta::imprime_informacoes_atleta(Atleta* a) {
    // Não precisamos saber se é Nadador ou Corredor.
    // Apenas pedimos para o atleta se imprimir.
    // O C++ vai chamar a versão correta do imprime_info() sozinho
    a->imprime_info();
}