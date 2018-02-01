#include <vector>
#include <iostream>
#include "Interpretation.h"

using namespace std;

void erreur(int numLigne, string erreur) {

    if(numLigne > 0)
        throw "Ligne " + to_string(numLigne) + " : " + erreur;
    else
        throw "Erreur : " + erreur;
}

void erreur(int numLigne) {
	erreur(numLigne, "Impossible d'interpreter cette ligne");
}

int chercherEgal(string ligne) {

	for(unsigned int i = 0 ; i < ligne.length() ; i++) {
		if(ligne[i]=='=') {
			return i;
		}
	}

	return -1;
}

Type trouverTypeNom(std::string nom, map<string, Matrice> matrices, map<string, Vecteur> vecteurs, map<string, float> nombres) {

    if(!nomValide(nom)) return invalide;

    for (map<string, Matrice>::iterator it=matrices.begin(); it!=matrices.end(); it++) {
        if(it->first == nom) return typeMatrice;
    }

    for (map<string, Vecteur>::iterator it=vecteurs.begin(); it!=vecteurs.end(); it++) {
        if(it->first == nom) return typeVecteur;
    }

    for (map<string, float>::iterator it=nombres.begin(); it!=nombres.end(); it++) {
        if(it->first == nom) return typeNombre;
    }

    return innexistant;
}

bool nomValide(string nom) {
	for(unsigned int i = 0 ; i < nom.length() ; i++) {
		if( !( (nom[i] >= 'a' && nom[i] <= 'z') || (nom[i] >= 'A' && nom[i] <= 'Z') ) ) {
			return false;
		}
	}

	return true;
}

Type trouverTypeValeur(string valeur) {

	if(valeur[0] == '[') {

		if(valeur.length() >= 2) {

			if(valeur[1] == '[')
				return (matriceValide(valeur) ? typeMatrice : invalide);

		}

		return (vecteurValide(valeur) ? typeVecteur : invalide);
	}
	else {
		return (nombreValide(valeur) ? typeNombre : invalide);
	}
}

bool matriceValide(string matrice) {
	if(matrice.length() < 5) return false;
	if(matrice.substr(matrice.length()-2) != "]]") return false;

	int taille = tailleMatrice(matrice);
	if(taille == 0) return false;

	int posDernierVecteur = 1;

	for(unsigned int i = 6 ; i < matrice.length()-2 ; i++) {

		if(matrice[i] == '[') {

			if(matrice.substr(i-2, 2) != ", ") return false;

			if(i - posDernierVecteur < 5) return false;

			string vecteur = matrice.substr(posDernierVecteur, i-posDernierVecteur-2);
			if(!vecteurValide(vecteur)) return false;
			if(tailleVecteur(vecteur) != taille) return false;

			posDernierVecteur = i;
		}
	}

	string vecteur = matrice.substr(posDernierVecteur, matrice.length()-1 - posDernierVecteur);
	if(!vecteurValide(vecteur)) return false;

	return true;
}

bool vecteurValide(string vecteur) {

	if(vecteur.length() < 3) return false;
	if(vecteur[vecteur.length()-1] != ']') return false;

	int posDerniereVirgule = -1;

	for(unsigned int i = 2 ; i < vecteur.length()-1 ; i++) {

		if(vecteur[i] == ',') {

			if(vecteur[i+1] != ' ') return false;

			if(i - posDerniereVirgule < 3) return false;

			string nombre = vecteur.substr(posDerniereVirgule+2, i-posDerniereVirgule-2);
			if(!nombreValide(nombre)) return false;

			posDerniereVirgule = i;
		}
	}

	if(vecteur.length()-1 - posDerniereVirgule < 3) return false;

	string nombre = vecteur.substr(posDerniereVirgule+2, vecteur.length()-1 - posDerniereVirgule-2);
	if(!nombreValide(nombre)) return false;

	return true;
}

bool nombreValide(string nombre) {

	int nbPoints = 0;
	for(unsigned int i = 0 ; i < nombre.length() ; i++) {
		if( (nombre[i] < '0' || nombre[i] > '9') && nombre[i] != '.' )
			return false;
		else if(nombre[i] == '.')
			nbPoints++;

		if(nbPoints > 1)
			return false;
	}

	return true;
}

int tailleMatrice(string matrice) {
    int compteur = 0;

    for(unsigned int i = 1 ; i < matrice.length()-1 ; i++) {
        if(matrice[i] == '[')
            compteur++;
    }

    return compteur;
}

int tailleVecteur(string vecteur) {

    int compteur = 1;

    for(unsigned int i = 1 ; i < vecteur.length()-1 ; i++) {
        if(vecteur[i] == ',')
            compteur++;
    }

    return compteur;
}

Matrice stringToMatrice(string matrice) {

    vector<Vecteur> tab;

	int posDernierVecteur = 1;

	for(unsigned int i = 6 ; i < matrice.length()-2 ; i++) {

		if(matrice[i] == '[') {
			string vecteur = matrice.substr(posDernierVecteur, i-posDernierVecteur-2);
            tab.push_back(stringToVecteur(vecteur));
			posDernierVecteur = i;
		}
	}

	string vecteur = matrice.substr(posDernierVecteur, matrice.length()-1 - posDernierVecteur);
	tab.push_back(stringToVecteur(vecteur));

    return Matrice(tab);
}

Vecteur stringToVecteur(string vecteur) {
    vector<float> tab;

    int posDerniereVirgule = -1;

	for(unsigned int i = 2 ; i < vecteur.length()-1 ; i++) {

		if(vecteur[i] == ',') {
			string nombre = vecteur.substr(posDerniereVirgule+2, i-posDerniereVirgule-2);
            tab.push_back(stof(nombre));
			posDerniereVirgule = i;
		}
	}

	string nombre = vecteur.substr(posDerniereVirgule+2, vecteur.length()-1 - posDerniereVirgule-2);
	tab.push_back(stof(nombre));

    return Vecteur(tab);
}
