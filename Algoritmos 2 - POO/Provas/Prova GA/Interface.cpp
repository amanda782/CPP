#include "Interface.h"

Interface::Interface(string nomeLoja) {
	minhaLoja = nomeLoja;
}
Interface::~Interface(){}

void Interface::executar() {
    int opcao;
    do {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao) {
        case 1: menuAdicionarProduto(); break;
        case 2: menuBuscarProduto(); break;
        case 3: menuListarInformacoes(); break;
        case 4: menuRemoverProduto(); break;
        case 5: menuEditarProduto(); break;
        case 6: menuValorTotalEstoque(); break;
        case 7: menuAplicarDesconto(); break;
        case 8: menuVerificarEstoque(); break;
        case 9: menuRealizarVenda(); break;
        case 10: menuVerificarAcimaValor(); break;
        case 0: cout << "Saindo do sistema..." << endl; break;
        default: cout << "Opcao invalida. Tente novamente." << endl; break;
        }
        cout << endl; // espaço para a próxima iteração
    } while (opcao != 0);
}
void Interface::exibirMenu() {
    cout << "--- BEM-VINDO AO SISTEMA DA LOJA ---" << endl;
    cout << "1. Adicionar Produto ao Estoque" << endl;    
    cout << "2. Buscar Produto (Imprimir Dados)" << endl; 
    cout << "3. Listar Informações da Loja" << endl;       
    cout << "4. Remover Produto do Estoque" << endl;     
    cout << "5. Editar Produto" << endl;                  
    cout << "6. Calcular Valor Total do Estoque" << endl; 
    cout << "7. Aplicar Desconto em Produto" << endl;      
    cout << "8. Verificar Estoque de um Produto" << endl;  
    cout << "9. Realizar Venda" << endl;                   
    cout << "10. Listar Produtos Acima de um Valor" << endl;
    cout << "0. Sair" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Escolha uma opcao: ";

}
int Interface::lerOpcao() {
    int opcao;
    while (!(cin >> opcao)) {
        cout << "Entrada inválida. Por favor, digite um número: ";
    }
    return opcao;
}
Produto* Interface::buscarProdutoPorCodigo() {
    int codigo;
    cout << "Digite o código de barras do produto: ";
    codigo = lerOpcao();

    Produto* p = minhaLoja.buscar_produto(codigo);
    if (p == nullptr) {
        cout << "Produto com código " << codigo << " não encontrado." << endl;
    }
    return p;
}
void Interface::menuAdicionarProduto() {
    cout << "Qual tipo de produto deseja adicionar?" << endl;
    cout << "1. Smartphone" << endl;
    cout << "2. Laptop" << endl;
    cout << "3. Tablet" << endl;
    int tipo = lerOpcao();

    if (tipo < 1 || tipo > 3) {
        cout << "Tipo inválido." << endl;
        return;
    }

    int codigo;
    string nome;
    float preco;

    cout << "Digite o código de barras [obrigatório]: "; 
    codigo = lerOpcao();
    cout << "Digite o nome: ";
    cin >> nome;
    cout << "Digite o preco: ";
    cin >> preco;

    Produto* p = nullptr;

    if (tipo == 1) { //smartphone
        int modelo;
        int armazenamento;
        cout << "Digite o modelo (int): ";
        cin >> modelo;
        cout << "Digite a capacidade de armazenamento (GB): ";
        armazenamento = lerOpcao();
        p = new Smartphone(nome, preco, codigo,  modelo, armazenamento);
    }
    else if (tipo == 2) { // laptop
        string marca;
        float tela;
        cout << "Digite a marca: ";
        cin >> marca;
        cout << "Digite o tamanho da tela (polegadas): ";
        cin >> tela;
     
        p = new Laptops(nome, preco, codigo, marca, tela);
    }
    else if (tipo == 3) { // Tablet 
        string marca;
        float bateria;
        cout << "Digite a marca: ";
        cin >> marca;
        cout << "Digite a duração da bateria (horas): ";
        cin >> bateria;
      
        p = new Tablet( nome, preco, codigo, marca, bateria);
    }

    minhaLoja.adicionar_ao_estoque(p);
}
void Interface::menuBuscarProduto() {
    int codigo;
    cout << "Digite o código de barras do produto a buscar: ";
    codigo = lerOpcao();
    
    minhaLoja.imprime_produto(codigo);
}
void Interface::menuListarInformacoes() {
    minhaLoja.imprime_info_loja();
}
void Interface::menuRemoverProduto() {
    int codigo;
    cout << "Digite o código de barras do produto a remover: ";
    codigo = lerOpcao();
    
    minhaLoja.remover_do_estoque(codigo);
}
void Interface::menuEditarProduto() {
    Produto* p = buscarProdutoPorCodigo();
    if (p != nullptr) {
     
        minhaLoja.editar_produto(p);
    }
}
void Interface::menuValorTotalEstoque() {
    minhaLoja.valor_total();
}
void Interface::menuAplicarDesconto() {
    Produto* p = buscarProdutoPorCodigo();
    if (p != nullptr) {
        float porcentagem;
        cout << "Digite a porcentagem do desconto (ex: 10.5): ";
        while (!(cin >> porcentagem)) {
            cout << "Valor inválido. Digite um número: ";
          
        }
       
        minhaLoja.aplicar_desconto(p, porcentagem);
    }
}
void Interface::menuVerificarEstoque() {
    Produto* p = buscarProdutoPorCodigo();
    if (p != nullptr) {
        
        int quantidade = minhaLoja.verifica_produto(p);
        if (quantidade > 0) {
            cout << "Produto: " << p->get_nome() << endl;
            cout << "Quantidade em estoque: " << quantidade << endl;
        }
    }
}
void Interface::menuRealizarVenda() {
    Produto* p = buscarProdutoPorCodigo();
    if (p != nullptr) {
        // Delega para o método da Loja
        minhaLoja.realizar_venda(p);
    }
}
void Interface::menuVerificarAcimaValor() {
    float preco;
    cout << "Listar produtos com valor acima de (R$): ";
    while (!(cin >> preco)) {
        cout << "Valor inválido. Digite um número: ";
    }
    
    minhaLoja.verificar_acima(preco);
}