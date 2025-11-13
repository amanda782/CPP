#include "ComputingProcess.h"
#include <fstream>

ComputingProcess::ComputingProcess():Processo() {

}

ComputingProcess::ComputingProcess(int pid, string equacao):Processo(pid), calculo(equacao) {
	PID = pid;
	calculoOriginal = equacao;

}

ComputingProcess::~ComputingProcess() {

}

void ComputingProcess:: execute() {
    cout << "--- Executando Processo de Calculo (PID: " << getPid() << ") ---" << endl;
    cout << "  Calculando: " << calculoOriginal << endl;

    double resultado = calculo.calcular();

    cout << "  Resultado: " << resultado << endl;
}

void ComputingProcess::imprimeProcesso() {
	cout << "Tipo do processo: ComputingProcess" << endl;
	cout << "PID do processo: " << PID << endl;
}

void ComputingProcess::save(ofstream& arquivo) {
    arquivo << "COMPUTE;" << getPid() << ";" << this->calculoOriginal <<endl;
}