#include "Processo.h"

Processo::Processo() {
	PID = 0;
}
Processo::Processo(int pid) {
	PID = pid;
}
Processo::~Processo() {

}
int Processo::getPid() {
	return PID;
}

