#include "PrintingProcess.h"
#include "Processo.h"
#include "Sistema.h"

PrintingProcess::PrintingProcess(int pid, FilaProcessos* fila):Processo(pid) {
	PID = pid;
	this->fila = fila;
}
PrintingProcess::PrintingProcess():Processo() {
	fila = nullptr;
}
PrintingProcess::~PrintingProcess() {

}
void PrintingProcess::execute() {
    cout << "Executando processo de PID: " << getPid() << " || (PrintingProcess)" << endl;

    if (fila->size() == 0) {
        cout << "Fila vazia" << endl;
        return;
    }

    cout << endl;
    cout << "Fila do pool de processos: " << endl;

    int voltas = fila->size();

    for (int i = 0; i < voltas; i++) {
        Processo* p = fila->removerProximo();

        if (p != nullptr) {
            p->imprimeProcesso();
            cout << endl;

            fila->inserir(p);
        }
    }
}

void PrintingProcess::imprimeProcesso() {
	cout << "Tipo do processo: PrintingProcess" << endl;
	cout << "PID do processo: " << getPid() << endl;
}
void PrintingProcess::save(ofstream& arquivo) {
	arquivo << "PRINT;" << getPid() <<endl;
}

