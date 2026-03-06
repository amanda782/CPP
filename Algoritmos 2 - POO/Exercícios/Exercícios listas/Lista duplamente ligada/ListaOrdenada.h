#pragma once
#include <iostream>

using namespace std;

// node generico agora com ponteiro anterior tb
template <typename T>
struct Node {
    T dado;
    Node<T>* proximo;
    Node<T>* anterior; // aponta pra quem ta atras

    Node(T val) {
        dado = val;
        proximo = nullptr;
        anterior = nullptr;
    }
};

template <typename T>
class ListaDuplamenteOrdenada {
private:
    Node<T>* head; // inicio
    Node<T>* tail; // fim, ajuda nas insercoes no final
    int quantidade;

public:
    ListaDuplamenteOrdenada();
    ~ListaDuplamenteOrdenada();

    // metodos principais
    void insert(T dado);
    bool remove(T dadoParaRemover);
    bool find(T dado);

    // metodos de visualizacao
    void print(); // imprime normal
    void printInverso(); // imprime de tras pra frente pra testar os ponteiros anterior
    bool isEmpty();
    int size();
    void limpar();

    // mistura duas listas
    void merge(ListaDuplamenteOrdenada<T>& outraLista);
};


template <typename T>
ListaDuplamenteOrdenada<T>::ListaDuplamenteOrdenada() {
    head = nullptr;
    tail = nullptr;
    quantidade = 0;
}

template <typename T>
ListaDuplamenteOrdenada<T>::~ListaDuplamenteOrdenada() {
    limpar();
}

// insere ordenado lidando com proximo e anterior
template <typename T>
void ListaDuplamenteOrdenada<T>::insert(T dado) {
    Node<T>* novo = new Node<T>(dado);

    // caso 1: lista vazia
    if (head == nullptr) {
        head = novo;
        tail = novo;
    }
    // caso 2: insere no inicio (menor que o head)
    else if (dado < head->dado) {
        novo->proximo = head;
        head->anterior = novo; // o antigo head aponta pra tras pro novo
        head = novo;
    }
    // caso 3: insere no meio ou fim
    else {
        Node<T>* atual = head;

        // procura o primeiro cara MAIOR que o novo dado
        while (atual != nullptr && atual->dado < dado) {
            atual = atual->proximo;
        }

        // se atual for null, chegamos no fim da lista e ninguem era maior
        // entao insere no final (depois do tail)
        if (atual == nullptr) {
            tail->proximo = novo;
            novo->anterior = tail;
            tail = novo; // atualiza o tail
        }
        else {
            // insere ANTES do 'atual' (no meio da lista)
            Node<T>* anteriorDoAtual = atual->anterior;

            // liga o novo no anterior e no atual
            anteriorDoAtual->proximo = novo;
            novo->anterior = anteriorDoAtual;

            novo->proximo = atual;
            atual->anterior = novo;
        }
    }
    quantidade++;
}

template <typename T>
bool ListaDuplamenteOrdenada<T>::remove(T dadoParaRemover) {
    if (head == nullptr) return false;

    Node<T>* atual = head;

    while (atual != nullptr) {
        // achei o que quero remover
        if (atual->dado == dadoParaRemover) {

            // se nao for o head, arruma o ponteiro do anterior
            if (atual->anterior != nullptr) {
                atual->anterior->proximo = atual->proximo;
            }
            else {
                head = atual->proximo; // se for head, o proximo vira head
            }

            // se nao for o tail, arruma o ponteiro do proximo
            if (atual->proximo != nullptr) {
                atual->proximo->anterior = atual->anterior;
            }
            else {
                tail = atual->anterior; // se for tail, o anterior vira tail
            }

            delete atual;
            quantidade--;
            return true;
        }

        // otimizacao: se ja passou do valor, nao ta na lista
        if (atual->dado > dadoParaRemover) return false;

        atual = atual->proximo;
    }

    return false;
}

template <typename T>
bool ListaDuplamenteOrdenada<T>::find(T dado) {
    Node<T>* atual = head;
    while (atual != nullptr) {
        if (atual->dado == dado) return true;
        if (atual->dado > dado) return false; // paramos de procurar pq ja passou
        atual = atual->proximo;
    }
    return false;
}

template <typename T>
void ListaDuplamenteOrdenada<T>::merge(ListaDuplamenteOrdenada<T>& outraLista) {
    Node<T>* atual = outraLista.head;
    // percorre a outra lista e insere na nossa
    while (atual != nullptr) {
        this->insert(atual->dado);
        atual = atual->proximo;
    }
}

template <typename T>
void ListaDuplamenteOrdenada<T>::print() {
    Node<T>* atual = head;

    if (atual == nullptr) {
        cout << "lista vazia" << endl;
        return;
    }

    cout << "HEAD -> ";
    while (atual != nullptr) {
        cout << "[" << atual->dado << "]";
        if (atual->proximo != nullptr) cout << " <-> "; // setinha dupla pq eh duplamente ligada
        atual = atual->proximo;
    }
    cout << endl;
}

// imprime usando os ponteiros ANTERIOR pra ver se nao quebrou nada
template <typename T>
void ListaDuplamenteOrdenada<T>::printInverso() {
    Node<T>* atual = tail; // comeca do fim

    cout << "TAIL -> ";
    while (atual != nullptr) {
        cout << "[" << atual->dado << "]";
        if (atual->anterior != nullptr) cout << " <-> ";
        atual = atual->anterior; // anda pra tras
    }
    cout << endl;
}

template <typename T>
bool ListaDuplamenteOrdenada<T>::isEmpty() {
    return head == nullptr;
}

template <typename T>
int ListaDuplamenteOrdenada<T>::size() {
    return quantidade;
}

template <typename T>
void ListaDuplamenteOrdenada<T>::limpar() {
    Node<T>* atual = head;
    while (atual != nullptr) {
        Node<T>* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    head = nullptr;
    tail = nullptr;
    quantidade = 0;
}