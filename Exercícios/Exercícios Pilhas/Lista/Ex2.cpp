#include "Pilha.h"
#include <cstdlib>
#include <ctime>

bool equilibrio(string s) {
	Pilha<char> p1;
	for (char caractere : s) {
		if (caractere == '(' || caractere == '[' || caractere == '{')
			p1.push(caractere);
		
		if (caractere == ')' || caractere == ']' || caractere == '}') {
			if (p1.topNode() == nullptr)
					return false;
			char topo = p1.top();
			if (caractere == ')' && topo == '(' || caractere == ']' && topo == '[' || caractere == '}' && topo == '{')
				p1.pop();
			else
				return false;
		}
	}
	if (p1.size() == 0)
		return true;
	else
		return false;
}
int main() {
	
	string s = "";
	bool resposta = equilibrio(s);
	cout << resposta << endl;
	
	return 0;
}