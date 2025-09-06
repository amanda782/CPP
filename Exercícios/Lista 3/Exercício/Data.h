#pragma once
#include <iostream>
#include <string>

using namespace std;

class Data {
	public:
		Data();
		Data(int dia, int mes, int ano);
		~Data();

		//metodos:
		void imprime_data();
		int get_dia();
		int get_mes();
		int get_ano();

private:
	int d;
	int m;
	int a;
};