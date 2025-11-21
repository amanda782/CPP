#pragma once
#include <iostream>

using namespace std;

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
class Fila {
public:
    Fila();
    ~Fila();

    
    void push(T dado);      // insere no final
    T pop();                // remove do início e retorna
    T front();              // apenas olha o início sem remover
    bool isEmpty();         // verifica se está vazia
    int size();             // retorna tamanho atual


    bool find(T dadoProcurado);
    T removerEspecifico(T dadoParaRemover); // melhor colocar na classe que vai usar
    void print();
    void limpar();

private:
    Node<T>* head; //inicio da fila (onde sai)
    Node<T>* tail; // fim da fila (onde entra)
    int quantidade; // pra buscas
};

template <typename T>
Fila<T>::Fila() {
    head = nullptr;
    tail = nullptr;
    quantidade = 0;
}

template <typename T>
Fila<T>::~Fila() {
    limpar();
}

template <typename T>
void Fila<T>::push(T dado) {
    Node<T>* novo = new Node<T>(dado);

    if (head == nullptr) {
        // fila vazia
        head = novo;
        tail = novo;
    }
    else {
        // fila ja tinha gente
        tail->proximo = novo; // o atual ultimo aponta pro novo
        tail = novo;          // o novo vira o último
    }
    quantidade++;
}

template <typename T>
T Fila<T>::pop() {
    if (head == nullptr) {
        // retorna valor padrão do tipo T se vazia (0, "", etc). cuidar os retornos quando chamar o metodo!!
        return T();
    }

    Node<T>* temp = head; // armazena o primeiro node
    T valorSalvo = temp->dado; // aarmazena o primeiro valor

    head = head->proximo;
    if (head == nullptr) {
        tail = nullptr; // se a fila esvaziou, zera o tail também
    }

    delete temp;
    quantidade--;
    return valorSalvo;
}

// olhar o primeiro 
template <typename T>
T Fila<T>::front() {
    if (head != nullptr) {
        return head->dado; // retorna o primeiro elemento da fila
    }
    return T();
}

template <typename T>
bool Fila<T>::isEmpty() {
    return quantidade == 0; // (ou head == nullptr). se a quantidade for igual a zero vai retornar verdadeiro.
}

template <typename T>
int Fila<T>::size() {
    return quantidade;
}

// buscar rodando na fila
template <typename T>
bool Fila<T>::find(T dadoProcurado) {
    bool encontrado = false;
    int voltas = quantidade; // salva o tamanho inicial

    for (int i = 0; i < voltas; i++) {
        // tira o primeiro
        T val = this->pop();

        // verifica se é ele
        if (val == dadoProcurado) {
            encontrado = true;
            // não damos break aqui para a fila terminar de rodar e voltar ao tamanho original
        }

        // devolve para o final da fila
        this->push(val);
    }

    return encontrado;
}

// remover especifico rodando a fila
template <typename T>
T Fila<T>::removerEspecifico(T dadoParaRemover) {
    int voltas = quantidade;
    T valorRetornado = T(); // valor padrão caso não ache
    bool jaRemoveu = false;

    for (int i = 0; i < voltas; i++) {
        //tira o primeiro
        T val = this->pop();

        //é o que queremos remover? e ainda não removemos?
        if (val == dadoParaRemover && !jaRemoveu) {
            // entao uardamos o valor e NÃO devolvemos para a fila (push)
            valorRetornado = val;
            jaRemoveu = true; // a partir daqui, nunca mais entra nessa verificacao/bloco de codigo
            // o item foi removido pois não demos push
        }
        else {
            //caso nao seja oq queremos, devolvemos para o final da fila
            this->push(val); //pusha o elemento que acabei de tirar do fim da fila
        }
    }

    return valorRetornado;
}

template <typename T>
void Fila<T>::print() {
    int voltas = quantidade;

    cout << "INICIO -> ";
    for (int i = 0; i < voltas; i++) {
        T val = this->pop(); //cria uma nova variavel pra armazenar o primeiro da fila

        cout << "[" << val << "] "; // imprime

        this->push(val); // devolve pro final
    }
    cout << "<- FIM" << endl;
}

template <typename T>
void Fila<T>::limpar() {
    while (!isEmpty()) {
        pop();
    }
}