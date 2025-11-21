//FILA COM PRIORIDADE GENERICA
#pragma once
#include <iostream>
#include <string>

using namespace std;

//(T para dado, P para prioridade)
template <typename T, typename P>
struct Node {
    T dado;
    P prioridade; // P pode ser int, float, string...
    Node<T, P>* proximo;

    Node(T val, P prio) {
        dado = val;
        prioridade = prio;
        proximo = nullptr;
    }
};

template <typename T, typename P>
class Fila {
public:
    Fila();
    ~Fila();

    // push recebe P na prioridade
    void push(T dado, P prioridade);

    T pop();
    T front();
    P frontPrio(); // retorna a prioridade

    bool isEmpty();
    int size();
    bool find(T dadoProcurado);
    T removerEspecifico(T dadoParaRemover);

    void print();
    void limpar();

private:
    Node<T, P>* head;
    Node<T, P>* tail;
    int quantidade;

    void pushBack(T dado, P prioridade); //ferramenta INTERNA para rotação
};

// IMPLEMENTAÇÃO

template <typename T, typename P>
Fila<T, P>::Fila() {
    head = nullptr;
    tail = nullptr;
    quantidade = 0;
}

template <typename T, typename P>
Fila<T, P>::~Fila() {
    limpar();
}

// PUSH COM ROTAÇÃO, sempre comparando a prioridade
template <typename T, typename P>
void Fila<T, P>::push(T dado, P prioridade) {
    if (isEmpty()) {
        pushBack(dado, prioridade);
        return;
    }

    int voltas = quantidade;
    bool inseriu = false;

    for (int i = 0; i < voltas; i++) {
        P prioAtual = this->frontPrio();
        T dadoAtual = this->front();

        // COMPARAÇÃO GENÉRICA:
        if (!inseriu && prioridade > prioAtual) {
            pushBack(dado, prioridade);
            inseriu = true;
        }

        this->pop();
        pushBack(dadoAtual, prioAtual);
    }

    if (!inseriu) {
        pushBack(dado, prioridade);
    }
}

template <typename T, typename P>
void Fila<T, P>::pushBack(T dado, P prioridade) {
    Node<T, P>* novo = new Node<T, P>(dado, prioridade);
    if (head == nullptr) {
        head = novo;
        tail = novo;
    }
    else {
        tail->proximo = novo;
        tail = novo;
    }
    quantidade++;
}

template <typename T, typename P>
T Fila<T, P>::pop() {
    if (head == nullptr) 
        return T();

    Node<T, P>* temp = head;
    T valorSalvo = temp->dado;

    head = head->proximo;
    if (head == nullptr) tail = nullptr;

    delete temp;
    quantidade--;
    return valorSalvo;
}

template <typename T, typename P>
T Fila<T, P>::front() {
    if (head != nullptr) return head->dado;
    return T();
}

// retorna P 
template <typename T, typename P>
P Fila<T, P>::frontPrio() {
    if (head != nullptr) return head->prioridade;
    return P(); // retorna valor padrão de P (0, "")
}

template <typename T, typename P>
bool Fila<T, P>::isEmpty() {
    return quantidade == 0;
}

template <typename T, typename P>
int Fila<T, P>::size() {
    return quantidade;
}

template <typename T, typename P>
void Fila<T, P>::limpar() {
    while (!isEmpty()) 
        pop();
}

template <typename T, typename P>
void Fila<T, P>::print() {
    int voltas = quantidade;
    cout << "INICIO -> ";
    for (int i = 0; i < voltas; i++) {
        T val = front();
        P p = frontPrio();
        pop();

        cout << "[" << val << "|P:" << p << "] ";

        pushBack(val, p);
    }
    cout << "<- FIM" << endl;
}
template <typename T, typename P>
T Fila<T, P>::removerEspecifico(T dadoParaRemover) {
    int voltas = quantidade;
    T valorRetornado = T(); 
    bool jaRemoveu = false;

    for (int i = 0; i < voltas; i++) {
        //precisamos pegar O DADO e A PRIORIDADE antes de remover
        T val = this->front();
        P prio = this->frontPrio();

        // remove do início
        this->pop();

        // verifica se é o alvo e ainda nao removemos
        if (val == dadoParaRemover && !jaRemoveu) {
            // se sim, guardamos o valor e nao devolvemos para a fila
            valorRetornado = val;
            jaRemoveu = true;
        }
        else {
            // se nao é o alvo, devolvemos para o final
            // usamos pushBack para forçar ele a ir pro final
            this->pushBack(val, prio);
        }
    }

    return valorRetornado;
}
template <typename T, typename P>
bool Fila<T, P>::find(T dadoProcurado) {
    bool encontrado = false;
    int voltas = quantidade;

    for (int i = 0; i < voltas; i++) {
        T val = this->front();
        P prio = this->frontPrio();
        this->pop();

        if (val == dadoProcurado) {
            encontrado = true;
        }

        // Devolve pro final mantendo a prioridade original
        this->pushBack(val, prio);
    }

    return encontrado;
}