#include "Vecteur.h"




/* Constructeurs */

Vecteur::Vecteur() {
	
}

Vecteur::Vecteur(vector<float> tab) {
	
	if(tab.size() < 1) {
		throw string("Erreur : Taille < 1");
	}
	
	this->tab = tab;
}




/* methodes statiques */

Vecteur Vecteur::vecteurNul(int taille) {
	
	if(taille < 1) {
		throw string("Erreur : Taille < 1");
	}
	
	Vecteur vecteur;
	for(int i = 0 ; i < taille ; i++) {
		vecteur.tab.push_back(0);
	}
	return vecteur;
}




/* Getters et setters */

int Vecteur::taille() {
	return tab.size();
}

float Vecteur::scalaire(int i) {
	
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(i > taille() || i < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}
	
	return tab[i-1];
}

float Vecteur::setScalaire(int i, float valeur) {
	
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(i > taille() || i < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}
	
	tab[i-1] = valeur;
}




/* Surcharge d'operateur */

Vecteur Vecteur::operator+(Vecteur V) {
	
	if(taille() == 0 || V.taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	if(taille() != V.taille()) {
		throw string("Erreur : Tailles differentes");
	}
	
	Vecteur res = vecteurNul(taille());
	
	for(int i = 1 ; i <= taille() ; i++) {
		float nb = this->scalaire(i) + V.scalaire(i);
		res.setScalaire(i, nb);
	}
	
	return res;
}

Vecteur Vecteur::operator+=(Vecteur V) {
	return *this = *this + V;
}

Vecteur Vecteur::operator-(Vecteur V) {		
	return *this + V*(-1);
}

Vecteur Vecteur::operator-=(Vecteur V) {
	return *this = *this - V;
}

Vecteur Vecteur::operator*(float k) {
	
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	
	Vecteur res = vecteurNul(taille());
	
	for(int i = 1 ; i <= taille() ; i++) {
		float nb = k * this->scalaire(i);
		res.setScalaire(i, nb);
	}
	
	return res;
}

Vecteur Vecteur::operator*=(float k) {
	return *this = *this * k;
}

bool Vecteur::operator==(Vecteur V) {
	
	if(taille() == 0 || V.taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	if(taille() != V.taille()) {
		throw string("Erreur : Tailles differentes");
	}
	
	bool isEqual = true;
	
	for(int i = 1 ; i <= taille() ; i++) {
		if(this->scalaire(i) != V.scalaire(i)) {
			isEqual = false;
		}
	}
	
	return isEqual;
}

bool Vecteur::operator!=(Vecteur V) {
	return !(*this==V);
}




/* methodes extarieurs a la classe Matrice */

Vecteur operator*(float k, Vecteur V) {
	return V*k;
}
