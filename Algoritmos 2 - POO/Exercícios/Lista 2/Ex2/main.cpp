#include "Empresa.h"
#include "Departamento.h"
#include "Funcionario.h"

#pragma once
#include <iostream>
#include <string>

using namespace std;


int main() {
    Empresa minhaEmpresa(...);
    minhaEmpresa.adicionarDepartamento(Departamento("TI"));

    Funcionario novoFunc("Joao Programador", 8000.0, Data(26, 9, 2025));

    // 1. Pega o departamento desejado
    Departamento* deptoTI = minhaEmpresa.buscarDepartamentoPorNome("TI");

    // 2. Chama o método a partir do objeto departamento
    if (deptoTI != nullptr) {
        deptoTI->adicionarFuncionario(novoFunc);
    }
}