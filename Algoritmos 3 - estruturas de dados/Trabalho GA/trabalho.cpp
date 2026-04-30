#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

// grau minimo t: cada no tem entre t-1 e 2t-1 chaves
// (exceto raiz, que pode ter entre 1 e 2t-1 chaves)

struct No {
    vector<int> chaves;
    vector<No*> filhos;
    bool folha;

    No(bool isFolha) {
        folha = isFolha;
    }
};

class ArvoreB {
private:
    int t; 
    No* raiz;

    //  Busca 

    No* buscaHelper(No* no, int chave) {
        int i = 0;
        // .size retorna unsigned, por isso colocamos int pra evitar warning na comparação
        while (i < (int)no->chaves.size() && chave > no->chaves[i]) 
        // vai parar quando o i for o index do numero menor que a chave sendo buscada (local onde deveria estar oq estamos procurando ou o ponteiro pro proximo nó)
            i++;

        if (i < (int)no->chaves.size() && chave == no->chaves[i]) // se estiver lá oq estamos buscando
            return no;

        if (no->folha) // se nao tiver nenhum ponteiro pra descer, nao encontramos
            return nullptr;

        return buscaHelper(no->filhos[i], chave);// vai chamar o buscaHelper passando o No de filhos onde deve estar oq estamos procurando e retornar o resultado dele
    }

    //  insercao 

    // divide o filho cheio `filho` na posicao i de `pai`
    void dividirFilho(No* pai, int i, No* filho) {
        No* novoNo = new No(filho->folha);

        // copia as ultimas t-1 chaves do filho para o novo no
        for (int j = 0; j < t - 1; j++)
            novoNo->chaves.push_back(filho->chaves[j + t]);

        // copia os filhos correspondentes (se nao for folha)
        if (!filho->folha) {
            for (int j = 0; j < t; j++)
                novoNo->filhos.push_back(filho->filhos[j + t]);
        }

        int chaveMeio = filho->chaves[t - 1];

        // reduz o filho original
        filho->chaves.resize(t - 1);
        if (!filho->folha)
            filho->filhos.resize(t);

        // insere novo no e chave do meio no pai
        pai->filhos.insert(pai->filhos.begin() + i + 1, novoNo);
        pai->chaves.insert(pai->chaves.begin() + i, chaveMeio);
    }

    void inserirNaoCheio(No* no, int chave) {
        int i = (int)no->chaves.size() - 1;

        if (no->folha) {
            no->chaves.push_back(0);
            while (i >= 0 && chave < no->chaves[i]) {
                no->chaves[i + 1] = no->chaves[i];
                i--;
            }
            no->chaves[i + 1] = chave;
        } else {
            while (i >= 0 && chave < no->chaves[i])
                i--;
            i++;

            if ((int)no->filhos[i]->chaves.size() == 2 * t - 1) {
                dividirFilho(no, i, no->filhos[i]);
                if (chave > no->chaves[i])
                    i++;
            }
            inserirNaoCheio(no->filhos[i], chave);
        }
    }

    //  remocao 

    // retorna o maior valor da subarvore esquerda do indice idx
    int predecessor(No* no, int idx) {
        No* cur = no->filhos[idx];
        while (!cur->folha)
            cur = cur->filhos[cur->filhos.size() - 1];
        return cur->chaves[cur->chaves.size() - 1];
    }

    // retorna o menor valor da subarvore direita do indice idx
    int sucessor(No* no, int idx) {
        No* cur = no->filhos[idx + 1];
        while (!cur->folha)
            cur = cur->filhos[0];
        return cur->chaves[0];
    }

    // empresta do irmao esquerdo
    void emprestarEsquerda(No* no, int idx) {
        No* filho = no->filhos[idx];
        No* irmao = no->filhos[idx - 1];

        filho->chaves.insert(filho->chaves.begin(), no->chaves[idx - 1]);

        if (!filho->folha) {
            filho->filhos.insert(filho->filhos.begin(), irmao->filhos.back());
            irmao->filhos.pop_back();
        }

        no->chaves[idx - 1] = irmao->chaves.back();
        irmao->chaves.pop_back();
    }

    // empresta do irmao direito
    void emprestarDireita(No* no, int idx) {
        No* filho = no->filhos[idx];
        No* irmao = no->filhos[idx + 1];

        filho->chaves.push_back(no->chaves[idx]);

        if (!filho->folha) {
            filho->filhos.push_back(irmao->filhos.front());
            irmao->filhos.erase(irmao->filhos.begin());
        }

        no->chaves[idx] = irmao->chaves.front();
        irmao->chaves.erase(irmao->chaves.begin());
    }

    // funde filho[idx] com filho[idx+1], descendo chaves[idx] do pai
    void fundir(No* no, int idx) {
        No* filho = no->filhos[idx];
        No* irmao = no->filhos[idx + 1];

        filho->chaves.push_back(no->chaves[idx]);

        for (int c : irmao->chaves)
            filho->chaves.push_back(c);

        if (!filho->folha) {
            for (No* f : irmao->filhos)
                filho->filhos.push_back(f);
        }

        no->chaves.erase(no->chaves.begin() + idx);
        no->filhos.erase(no->filhos.begin() + idx + 1);

        delete irmao;
    }

    // garante que filho[idx] tem pelo menos t chaves antes de descer
    void completar(No* no, int idx) {
        if (idx != 0 && (int)no->filhos[idx - 1]->chaves.size() >= t)
            emprestarEsquerda(no, idx);
        else if (idx != (int)no->filhos.size() - 1 && (int)no->filhos[idx + 1]->chaves.size() >= t)
            emprestarDireita(no, idx);
        else {
            if (idx != (int)no->filhos.size() - 1)
                fundir(no, idx);
            else
                fundir(no, idx - 1);
        }
    }

    void removerDoNo(No* no, int chave) {
        int idx = 0;
        while (idx < (int)no->chaves.size() && chave > no->chaves[idx])
            idx++;

        if (idx < (int)no->chaves.size() && no->chaves[idx] == chave) {
            // chave encontrada neste no
            if (no->folha) {
                no->chaves.erase(no->chaves.begin() + idx);
            } else {
                if ((int)no->filhos[idx]->chaves.size() >= t) {
                    int pred = predecessor(no, idx);
                    no->chaves[idx] = pred;
                    removerDoNo(no->filhos[idx], pred);
                } else if ((int)no->filhos[idx + 1]->chaves.size() >= t) {
                    int suc = sucessor(no, idx);
                    no->chaves[idx] = suc;
                    removerDoNo(no->filhos[idx + 1], suc);
                } else {
                    fundir(no, idx);
                    removerDoNo(no->filhos[idx], chave);
                }
            }
        } else {
            // chave nao esta neste no
            if (no->folha) {
                cout << "Chave " << chave << " nao encontrada na arvore." << endl;
                return;
            }

            bool ultimoFilho = (idx == (int)no->filhos.size() - 1);

            if ((int)no->filhos[idx]->chaves.size() < t)
                completar(no, idx);

            // Apos completar, o indice pode ter mudado se houve fusao no ultimo filho
            if (ultimoFilho && idx > (int)no->filhos.size() - 1)
                removerDoNo(no->filhos[idx - 1], chave);
            else
                removerDoNo(no->filhos[idx], chave);
        }
    }

    //  caminhamentos 

    void preOrdemHelper(No* no) {
        if (!no) return;
        for (int c : no->chaves)
            cout << c << " ";
        for (No* f : no->filhos)
            preOrdemHelper(f);
    }

    void emOrdemHelper(No* no) {
        if (!no) return;
        int n = (int)no->chaves.size();
        for (int i = 0; i < n; i++) {
            if (!no->folha)
                emOrdemHelper(no->filhos[i]);
            cout << no->chaves[i] << " ";
        }
        if (!no->folha)
            emOrdemHelper(no->filhos[n]);
    }

    void posOrdemHelper(No* no) {
        if (!no) return;
        for (No* f : no->filhos)
            posOrdemHelper(f);
        for (int c : no->chaves)
            cout << c << " ";
    }

    void destruir(No* no) {
        if (!no) return;
        for (No* f : no->filhos)
            destruir(f);
        delete no;
    }

    // gera o .dot recursivamente: atribui IDs aos nos e emite arestas
    void gerarDotHelper(No* no, ofstream& out, int& contador, map<No*, int>& ids) {
        int id = contador++;
        ids[no] = id;

        // monta o label do no no formato record: <p0>|chave|<p1>|...
        ostringstream label;
        label << "<p0>";
        for (int i = 0; i < (int)no->chaves.size(); i++)
            label << "|" << no->chaves[i] << "|<p" << (i + 1) << ">";

        out << "  node" << id
            << " [label=\"" << label.str() << "\""
            << ", shape=record, style=filled, fillcolor=lightblue];\n";

        // processa filhos antes de emitir arestas (IDs precisam existir)
        for (No* f : no->filhos)
            gerarDotHelper(f, out, contador, ids);

        // emite arestas deste no para cada filho
        for (int i = 0; i < (int)no->filhos.size(); i++) {
            out << "  node" << id << ":p" << i
                << " -> node" << ids[no->filhos[i]] << ";\n";
        }
    }

public:
    ArvoreB(int grau) : t(grau), raiz(nullptr) {}

    ~ArvoreB() { destruir(raiz); }

    No* buscar(int chave) {
        if (!raiz) return nullptr;
        return buscaHelper(raiz, chave);
    }

    void inserir(int chave) {
        if (!raiz) {
            raiz = new No(true);
            raiz->chaves.push_back(chave);
            return;
        }

        if ((int)raiz->chaves.size() == 2 * t - 1) {
            No* novaRaiz = new No(false);
            novaRaiz->filhos.push_back(raiz);
            dividirFilho(novaRaiz, 0, raiz);
            raiz = novaRaiz;
        }

        inserirNaoCheio(raiz, chave);
    }

    void remover(int chave) {
        if (!raiz) {
            cout << "Arvore vazia." << endl;
            return;
        }

        removerDoNo(raiz, chave);

        // se a raiz ficou vazia mas tem filho, promove o filho
        if (raiz->chaves.empty() && !raiz->folha) {
            No* velhaRaiz = raiz;
            raiz = raiz->filhos[0];
            delete velhaRaiz;
        }
    }

    void preOrdem() {
        cout << "Pre-ordem:  ";
        preOrdemHelper(raiz);
        cout << endl;
    }

    void emOrdem() {
        cout << "Em ordem:   ";
        emOrdemHelper(raiz);
        cout << endl;
    }

    void posOrdem() {
        cout << "Pos-ordem:  ";
        posOrdemHelper(raiz);
        cout << endl;
    }

    void gerarDot(const string& arquivo) {
        ofstream out(arquivo);
        out << "digraph ArvoreBt {\n";
        out << "  node [fontname=\"Helvetica\", fontsize=12];\n";
        out << "  edge [arrowsize=0.7];\n";
        if (raiz) {
            int contador = 0;
            map<No*, int> ids;
            gerarDotHelper(raiz, out, contador, ids);
        } else {
            out << "  vazio [label=\"(arvore vazia)\", shape=plaintext];\n";
        }
        out << "}\n";
        cout << "Arquivo .dot gerado: " << arquivo << endl;
    }
};
// testes

void separador(const string& titulo) {
    cout << "\n========== " << titulo << " ==========" << endl;
}

int main() {
    // t=2, arvore 2-3-4
    separador("Exemplo 1 - Insercoes sequenciais");
    {
        ArvoreB a(2);
        for (int v : {10, 20, 30, 40, 50})
            a.inserir(v);
        a.emOrdem();
        a.gerarDot("dotFiles/exemplo1_insercao_sequencial.dot");
    }

    // insercoes aleatorias causam splits (t=2)
    separador("Exemplo 2 - Insercoes que causam splits");
    {
        ArvoreB a(2);
        for (int v : {10, 20, 5, 6, 12, 30, 7, 17, 3, 15})
            a.inserir(v);
        a.emOrdem();
        a.gerarDot("dotFiles/exemplo2_splits.dot");
    }

    // remocao de folha (t=2)
    separador("Exemplo 3 - Remocao de folha");
    {
        ArvoreB a(2);
        for (int v : {10, 20, 5, 6, 12, 30, 7, 17, 3, 15})
            a.inserir(v);
        cout << "Antes de remover 6:" << endl;
        a.emOrdem();
        a.remover(6);
        a.remover(3);
        cout << "Apos remover 6 e 3:" << endl;
        a.emOrdem();
        a.gerarDot("dotFiles/exemplo3_remocao_folha.dot");
    }

    // remocao de no interno com fusao (t=2)
    separador("Exemplo 4 - Remocao de no interno");
    {
        ArvoreB a(2);
        for (int v : {10, 20, 5, 6, 12, 30, 7, 17, 3, 15})
            a.inserir(v);
        a.remover(20);
        a.remover(30);
        cout << "Apos remover 20 e 30:" << endl;
        a.emOrdem();
        a.gerarDot("dotFiles/exemplo4_remocao_interna.dot");
    }

    // arvore com grau maior (t=3, arvore 2-3-4-5-6) e remocoes consecutivas
    separador("Exemplo 5 - Grau t=3 com multiplas remocoes");
    {
        ArvoreB a(3);
        for (int v : {1, 3, 7, 10, 11, 13, 14, 15, 18, 16, 19, 24, 25, 26, 21, 4, 5, 20, 22, 2, 17, 12, 6})
            a.inserir(v);
        cout << "Arvore completa:" << endl;
        a.emOrdem();
        a.gerarDot("dotFiles/exemplo5_antes_remocoes.dot");

        for (int v : {6, 13, 7, 4, 2})
            a.remover(v);
        cout << "Apos remover 6, 13, 7, 4, 2:" << endl;
        a.emOrdem();
        a.gerarDot("dotFiles/exemplo5_apos_remocoes.dot");
    }

    return 0;
}
