#pragma once
#include <iostream>
#include <string>
#include <limits> 
#include "Loja.h"
#include "Smartphone.h"
#include "Laptops.h"
#include "Tablet.h"
using namespace std;

class Interface {
public:
    

    Interface(string nomeLoja);
    ~Interface();
    void executar();

    //organizando o menu
    void exibirMenu();
    int lerOpcao();
    Produto* buscarProdutoPorCodigo(); 

    // funcoes do menu
    void menuAdicionarProduto();     
    void menuBuscarProduto();        
    void menuListarInformacoes();    
    void menuRemoverProduto();       
    void menuEditarProduto();       
    void menuValorTotalEstoque();    
    void menuAplicarDesconto();      
    void menuVerificarEstoque();    
    void menuRealizarVenda();        
    void menuVerificarAcimaValor();  

private:
    Loja minhaLoja;
};