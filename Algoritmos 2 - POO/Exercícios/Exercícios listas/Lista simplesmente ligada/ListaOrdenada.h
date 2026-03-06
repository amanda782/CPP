#pragma once
#include <iostream>

using namespace std;


template <typename T>
struct Node {
    T dado;
    Node<T>* proximo;

    Node(T val) {
        dado = val;
        proximo = nullptr;
    }
};


template <typename T>
class ListaOrdenada {
private:
    Node<T>* head;
    int quantidade;

public:
    ListaOrdenada();
    ~ListaOrdenada();

    void insert(T dado);
    bool remove(T dadoParaRemover);
    bool find(T dado);
    void print();
    bool isEmpty();
    int size();
    void limpar();

    void merge(ListaOrdenada<T>& outraLista); //recebe outra lista e faz o mix
};


template <typename T>
ListaOrdenada<T>::ListaOrdenada() {
    head = nullptr;
    quantidade = 0;
}

template <typename T>
ListaOrdenada<T>::~ListaOrdenada() {
    limpar();
}

// INSERT INTELIGENTE: sabe exatamente onde inserir
template <typename T>
void ListaOrdenada<T>::insert(T dado) {
    Node<T>* novo = new Node<T>(dado);

    if (head == nullptr || dado < head->dado) {//casos em que insere no primeiro lugar
        novo->proximo = head;
        head = novo;
    }
    else {
        Node<T>* atual = head;
        while (atual->proximo != nullptr && atual->proximo->dado < dado) {
            atual = atual->proximo;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
    quantidade++;
}

template <typename T>
void ListaOrdenada<T>::merge(ListaOrdenada<T>& outraLista) {
    // podemos acessar 'head' privado pq somos da mesma classe
    Node<T>* atual = outraLista.head;

    while (atual != nullptr) {
        // pegamos o dado da outra lista e inserimos na nossa
        // o 'insert' já cuida de colocar na posição certa
        this->insert(atual->dado);

        atual = atual->proximo;
    }
    outraLista.limpar(); //acaba com a vida da outra lista
}

template <typename T>
bool ListaOrdenada<T>::remove(T dadoParaRemover) {
    if (head == nullptr) 
        return false;

    if (head->dado == dadoParaRemover) {
        Node<T>* temp = head;
        head = head->proximo;
        delete temp;
        quantidade--;
        return true;
    }

    Node<T>* atual = head;
    while (atual->proximo != nullptr) {
        if (atual->proximo->dado == dadoParaRemover) {
            Node<T>* temp = atual->proximo;
            atual->proximo = temp->proximo;
            delete temp;
            quantidade--;
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

template <typename T>
bool ListaOrdenada<T>::find(T dado) {
    Node<T>* atual = head;
    while (atual != nullptr) {
        if (atual->dado == dado)
            return true;
        if (atual->dado > dado) //se o de agora ja for maior, mais pra frente nao vai encontrar o alvo
            return false; 
        atual = atual->proximo;
    }
    return false;
}

template <typename T>
void ListaOrdenada<T>::print() {
    Node<T>* atual = head;
    if (atual == nullptr) {
        cout << "Lista Vazia" << endl;
        return;
    }
    cout << "HEAD -> ";
    while (atual != nullptr) {
        cout << "[" << atual->dado << "] ";
        if (atual->proximo != nullptr) {
            cout << " -> ";
        }
        atual = atual->proximo;
    }
    cout << endl;
}

template <typename T>
bool ListaOrdenada<T>::isEmpty() {
    return head == nullptr;
}

template <typename T>
int ListaOrdenada<T>::size() {
    return quantidade;
}

template <typename T>
void ListaOrdenada<T>::limpar() {
    Node<T>* atual = head;
    while (atual != nullptr) {
        Node<T>* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    head = nullptr;
    quantidade = 0;
}