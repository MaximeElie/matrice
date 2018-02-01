#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <istream>
#include <map>

#include "Matrice.h"
#include "Vecteur.h"
#include "Interpretation.h"

using namespace std;

int main(int argc, char *argv[]) {

	try {

	    istream* input = nullptr;

        if(argc == 1) {
            input = &cin;
        }
        else if(argc == 2) {
            ifstream* inputFile = new ifstream(argv[1]);

            if(*inputFile)
                input =inputFile;
            else
                throw string("Impossible de lire le fichier...");
        }
        else {
            throw string("Erreur d'arguments...");
        }

		map<string, Matrice> matrices;
		map<string, Vecteur> vecteurs;
		map<string, float> nombres;

		string ligne;
		int numLigne = 0;

        if(input == &cin) cout << "> ";

		while(getline(*input, ligne)) {

            if(input != &cin) numLigne++;

            if(ligne.length()==0) {
                if(input == &cin) cout << endl << "> ";
                continue;
            }

            int posEgal = chercherEgal(ligne);

            try {

                if(posEgal == 0 && (int)ligne.length()==1) {
                    erreur(numLigne, "termes a gauche et a droite du '=' manquants");
                }
                else if(posEgal == 0) {
                    erreur(numLigne, "terme a gauche du '=' manquant");
                }
                else if(posEgal == (int)ligne.length()-1) {
                    erreur(numLigne, "terme a droite du '=' manquant");
                }

                if(posEgal != -1) {
                    string nom = ligne.substr(0, posEgal);
                    string valeur = ligne.substr(posEgal+1);

                    if(!nomValide(nom)) {
                        erreur(numLigne, "le nom \"" + nom + "\" n'est pas valide");
                    }

                    switch(trouverTypeValeur(valeur)) {
                        case typeMatrice: matrices[nom]=stringToMatrice(valeur); break;
                        case typeVecteur: vecteurs[nom]=stringToVecteur(valeur); break;
                        case typeNombre: nombres[nom]=stof(valeur); break;
                        case invalide : erreur(numLigne, "\"" + valeur + "\" n'est pas une donnee valide"); break;
                        default: break;
                    }

                    if(input == &cin) cout << endl << "> ";
                    continue;
                }

                if(ligne.length() > 1) if(ligne[0] == ':') {

                    switch(trouverTypeNom(ligne.substr(1), matrices, vecteurs, nombres)) {
                        case typeMatrice: cout << endl << ligne.substr(1) << " = " << matrices[ligne.substr(1)] << endl; break;
                        case typeVecteur: cout << endl << ligne.substr(1) << " = " << vecteurs[ligne.substr(1)] << endl; break;
                        case typeNombre: cout << endl << ligne.substr(1) << " = " << nombres[ligne.substr(1)] << endl; break;
                        case invalide : erreur(numLigne, "\"" + ligne.substr(1) + "\" n'est pas un nom valide"); break;
                        case innexistant : erreur(numLigne, "\"" + ligne.substr(1) + "\" n'existe pas"); break;
                        default: break;
                    }

                    if(input == &cin) cout << endl << "> ";
                    continue;
                }

                if(ligne.length() == 4) if(ligne.substr(0) == "exit") {
                    return 0;
                }

                erreur(numLigne);
            }
            catch(string e) {
                cout << endl << e << endl;
            }

            if(input == &cin) cout << endl << "> ";
        }
	}
	catch(string e) {
		cout << endl << endl << e << endl;
	}

	return 0;
}
