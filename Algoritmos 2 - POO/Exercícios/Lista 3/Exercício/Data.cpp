
#include "Data.h"

Data::Data() {
	d = 0;
	m = 0;
	a = 0;
}

Data::Data(int dia, int mes, int ano) {
	d = dia;
	m = mes;
	a = ano;
}

Data::~Data(){}

void Data::imprime_data() {
	cout << d << "/" << m << "/" << a << endl;

}

int Data::get_dia() {
	return d;
}
int Data::get_mes() {
	return m;
}
int Data::get_ano() {
	return a;
}

