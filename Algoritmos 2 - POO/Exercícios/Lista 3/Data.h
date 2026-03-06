#pragma once
#include <iostream>
#include <string>

using namespace std;

class Data {
public:
	Data();
	Data(int day, int month, int year);
	~Data();

	void imprime_data();
	int get_dia();
	int get_mes();
	int get_ano();

private:
	int dia;
	int mes;
	int ano;
};