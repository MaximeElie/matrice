#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include "Matrice.h"
#include "Vecteur.h"

using namespace std;

int chercherEgal(string ligne) {
	
	for(int i = 0 ; i < ligne.length() ; i++) {
		if(ligne[i]=='=') {
			return i;
		}
	}
	
	return -1;
}

int main(int argc, char *argv[]) {
	
	if(argc != 2) {
		cout << endl << "Erreur d'arguments..." << endl << endl;
		system("pause");
		return 0;
	}
	
	ifstream input(argv[1]);
	
	if(!input) {
		cout << endl << "Impossible de lire le fichier..." << endl << endl;
		system("pause");
		return 0;
	}
	
	map<string, Matrice> matrices;
	map<string, Vecteur> vecteurs;
	map<string, float> nombres;
	
	try {
		
		string ligne;
		int numLigne = 0;
		
		while(getline(input, ligne)) {
			numLigne++;
			if(ligne.length()==0) {
				continue;
			}
			
			int posEgal = chercherEgal(ligne);
			
			if(posEgal == 0 || posEgal == ligne.length()-1) {
				throw numLigne;
			}
			
			if(posEgal != -1) {
				
			}
		}
		
	}
	catch(string e) {
		cout << endl << endl << e << endl;
	}
	catch(int e) {
		cout << endl << "Erreur a la ligne " << e << endl;
	}
	
	cout << endl;
	system("pause");
	return 0;
}