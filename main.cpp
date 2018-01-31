#include <iostream>
#include "Matrice.h"
#include "Vecteur.h"

using namespace std;

int main() {
	
	try {
		Matrice M = Matrice::saisir();
		cout << endl << "M:";
		M.afficher();
		cout << endl << "inverse:";
		(M^-1).afficher();
	}
	catch(string erreur) {
		cout << endl << endl << erreur << endl;
	}
	
	cout << endl;
	
	return 0;
}