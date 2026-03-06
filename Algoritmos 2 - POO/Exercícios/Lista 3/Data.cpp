#include "Data.h"

Data::Data() {
	dia = 0;
	mes = 0;
	ano = 0;
}

Data::Data(int day, int month, int year) {
	dia = day;
	mes = month;
	ano = year;
}

Data::~Data(){}

void Data::imprime_data() {
	cout << dia << "/" << mes << "/" << ano << endl;
}

int Data::get_dia() {
	return dia;
}

int Data::get_mes() {
	return mes;
}

int Data::get_ano() {
	return ano;
}