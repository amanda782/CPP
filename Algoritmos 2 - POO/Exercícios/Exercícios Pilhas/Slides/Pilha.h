#pragma once
#include <iostream>

using namespace std;
/*exemplos de como instanciar:
 Pilha<char> p1;   pilha de char
Pilha<int> p2;    pilha de int
Pilha<double> p3;  pilha de doubles
*/

template <typename T>
struct Node {
    T dado;              
    Node<T>* proximo;    

    Node(T dado) {
        this->dado = dado;
        proximo = nullptr;
    }
};


template <typename T>
class Pilha {
public:
    Pilha();
    Pilha(Node<T>* first); // construtor recebe Node<T>*
    ~Pilha();

    void push(T dado);     
    T top();            
    void pop();
    bool find(T dado);   
    Node<T>* topNode();
    T removerEspecifico(T dadoParaRemover); 
    void imprimir();
    int size();

private:
    Node<T>* topo;  
    int tamanho;
};

template <typename T>
Pilha<T>::Pilha(Node<T>* first) {
    topo = first;
}

template <typename T>
Pilha<T>::Pilha() {
    topo = nullptr;
}

template <typename T>
Pilha<T>::~Pilha() {
    while (topo != nullptr) {
        pop();
    }
}

template <typename T>
void Pilha<T>::push(T dado) {
    Node<T>* n = new Node<T>(dado); // cria Node<T>
    n->proximo = topo;
    topo = n;
    tamanho++;
}

template <typename T>
T Pilha<T>::top() {
    if (topo != nullptr)
        return topo->dado;

    return T(); //aqui retorna um valor padrao, dependendo do tipo de variavel que estamos usando(0, ' ', " ")
}

template <typename T>
Node<T>* Pilha<T>::topNode() {
    return topo;
}

template <typename T>
bool Pilha<T>::find(T dado) {
    Node<T>* atual = topo; //armazena o topo
    while (atual != nullptr) { // enquanto a lista nao estiver vazia
        if (atual->dado == dado) { // verifica se o atual possui o dado que procuramos como atributo
            return true; 
        }
        atual = atual->proximo; // atualiza pra ir pro proximo
    }
    return false;
}

template <typename T>
void Pilha<T>::pop() {
    if (topo != nullptr) {
        Node<T>* noRemover = topo; //armazena o topo. vamos remover ele
        Node<T>* novoTopo = noRemover->proximo; // o de baixo do topo é o novo topo
        topo = novoTopo;  //define o novotopo como topo
        delete noRemover;
        tamanho--;
    }
}

template <typename T>
T Pilha<T>::removerEspecifico(T dadoParaRemover) {
    Pilha<T> pilhaAuxiliar; // pilha auxiliar também é <T>
    T valorRetornado = T(); // inicializa com valor padrão (ex 0 ou vazio)
    bool encontrado = false;

    // desempilhar até achar
    while (this->topo != nullptr) {
        T valorNoTopo = this->top(); // armazena o topo DESSA pilha. como se fosse ela mesma o this
        this->pop(); //chama o metodo pra remover dela mesma

        if (valorNoTopo == dadoParaRemover) {
            valorRetornado = valorNoTopo;
            encontrado = true;
            tamanho--;
            break;
        }
        else {
            pilhaAuxiliar.push(valorNoTopo);
        }
    }

    // devolvendo para a original
    while (pilhaAuxiliar.topo != nullptr) {
        T resgate = pilhaAuxiliar.top();
        pilhaAuxiliar.pop();
        this->push(resgate);
    }

    return valorRetornado;
}

template <typename T>
void Pilha<T>::imprimir() {
    if (topo == nullptr) {
        cout << "[Pilha Vazia]" << endl;
        return;
    }

    Node<T>* atual = topo; // começa um ponteiro auxiliar no topo

    cout << "--- TOPO ---" << endl;

    // percorre a lista "descendo" as camadas
    while (atual != nullptr) {
        cout << "|  " << atual->dado << "  |" << endl; // Imprime o valor
        atual = atual->proximo; // Avança para o de baixo
    }

    cout << "--- BASE ---" << endl;
}

template <typename T>
int Pilha<T>::size() {
    return tamanho;
}