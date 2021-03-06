#include <cmath>
#include "Matrice.h"


/* Constructeurs */

Matrice::Matrice() {

}

Matrice::Matrice(vector<Vecteur> tab) {

	if(tab.size() < 1) {
		throw string("Erreur : Taille < 1");
	}

	for(int i = 0 ; i < (int)tab.size() ; i++) {
		if(tab[i].taille() != (int)tab.size()) {
			throw string("Erreur : Mauvaises dimensions");
		}
	}

	this->tab = tab;
}




/* methodes statiques */

Matrice Matrice::matriceNulle(int taille) {

	if(taille < 1) {
		throw string("Erreur : Taille < 1");
	}

	Matrice matrice;

	for(int i = 0 ; i < taille ; i++) {
		matrice.tab.push_back(Vecteur::vecteurNul(taille));
	}

	return matrice;
}

Matrice Matrice::matriceIdentite(int taille) {
	Matrice matrice = matriceNulle(taille);

	for(int i = 1 ; i <= taille ; i++) {
		matrice[i][i] = 1;
	}

	return matrice;
}




/* methodes utiles */

string Matrice::toString() {
    string str = "[";

    for(int i = 1 ; i < taille() ; i++) {
        str += (*this)[i].toString() + ", ";
    }

    str += (*this)[taille()].toString() + "]";

    return str;
}

int Matrice::taille() {
	return this->tab.size();
}




/* Getters et setters */

Vecteur Matrice::getLigne(int i) {

	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(i > taille() || i < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	return tab[i-1];
}

void Matrice::setLigne(int i, Vecteur ligne) {

	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(ligne.taille() == 0) {
		throw string("Erreur : ligne vide");
	}
	else if(taille() != ligne.taille()) {
		throw string("Erreur : Tailles differentes");
	}
	else if(i > taille() || i < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	tab[i-1] = ligne;
}

Vecteur Matrice::getColonne(int j) {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(j > taille() || j < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	Vecteur colonne = Vecteur::vecteurNul(taille());
	for(int i = 1 ; i <= taille() ;i++) {
		colonne[i] = (*this)[i][j];
	}

	return colonne;
}

void Matrice::setColonne(int j, Vecteur colonne) {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(colonne.taille() == 0) {
		throw string("Erreur : colonne vide");
	}
	else if(taille() != colonne.taille()) {
		throw string("Erreur : Tailles differentes");
	}
	else if(j > taille() || j < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	for(int i = 1 ; i <= taille() ; i++) {
		(*this)[i][j] = colonne[i];
	}
}




/* Opérations avancées */

float Matrice::mineur(int i, int j) {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(i > taille() || i < 1 || j > taille() || j < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	if(taille()==1) {
		return (*this)[1][1];
	}

	vector<Vecteur> tabMatrice;

	for(int ii = 1 ; ii <= taille() ; ii++) {
		vector<float> tabVecteur;
		for(int jj = 1 ; jj <= taille() ; jj++) {
			if(jj!=j) {
				tabVecteur.push_back((*this)[ii][jj]);
			}
		}
		if(ii!=i) {
			tabMatrice.push_back(Vecteur(tabVecteur));
		}
	}

	Matrice matrice(tabMatrice);

	return matrice.determinant();
}

float Matrice::cofacteur(int i, int j) {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(i > taille() || i < 1 || j > taille() || j < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	return pow(-1, i+j)*mineur(i,j);
}

float Matrice::determinant() {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}

	if(taille()==1) {
		return (*this)[1][1];
	}

	float res = 0;
	for(int i = 1 ; i <= taille() ; i++) {
		res += (*this)[i][1] * cofacteur(i, 1);
	}

	return res;
}

Matrice Matrice::comatrice() {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}

	Matrice res = Matrice::matriceNulle(taille());

	for(int i = 1 ; i <= taille() ; i++) {
		for(int j = 1 ; j <= taille() ; j++) {
			res[i][j] = cofacteur(i,j);
		}
	}

	return res;
}

Matrice Matrice::transpose() {

	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}

	Matrice res = matriceNulle(taille());

	for(int i = 1 ; i <= taille() ; i++) {
		res.setLigne(i, this->getColonne(i));
	}

	return res;
}

Matrice Matrice::inverse() {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}

	if(determinant()==0) {
		throw string("Erreur : Matrice non inversible");
	}

	return comatrice().transpose() * (1/determinant());
}




/* Surcharge d'operateur */

Matrice Matrice::operator+(Matrice M) {

	if(taille() == 0 || M.taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	if(taille() != M.taille()) {
		throw string("Erreur : Tailles differentes");
	}

	Matrice res = matriceNulle(taille());

	for(int i = 1 ; i <= taille() ; i++) {
		res[i] = (*this)[i] + M[i];
	}

	return res;
}

Matrice Matrice::operator+=(Matrice M) {
	return *this = *this + M;
}

Matrice Matrice::operator-(Matrice M) {
	return *this + M*(-1);
}

Matrice Matrice::operator-=(Matrice M) {
	return *this = *this - M;
}

Matrice Matrice::operator*(Matrice M) {

	if(taille() == 0 || M.taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	if(taille() != M.taille()) {
		throw string("Erreur : Tailles differentes");
	}

	Matrice res = matriceNulle(taille());

	for(int i = 1 ; i <= taille() ; i++) {
		for(int j = 1 ; j <= taille() ; j++) {
			float nb = 0;
			for(int k = 1 ; k <= taille() ; k++) {
				nb += (*this)[i][k] * M[k][j];
			}
			res[i][j] = nb;
		}
	}

	return res;
}

Matrice Matrice::operator*=(Matrice M) {
	return *this = *this * M;
}

Matrice Matrice::operator*(float k) {

	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}

	Matrice res = matriceNulle(taille());

	for(int i = 1 ; i <= taille() ; i++) {
		res[i] = k * (*this)[i];
	}

	return res;
}

Matrice Matrice::operator*=(float k) {
	return *this = *this * k;
}

Matrice Matrice::operator^(int n) {

	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}

	Matrice res;

	if(n == 0) {
		res = matriceIdentite(taille());
	}
	else if(n>0) {

		res = *this;

		for(int i = 1 ; i < n ; i++) {
			res*=*this;
		}
	}
	else {
		res = (this->inverse())^-n;
	}

	return res;
}

Matrice Matrice::operator^=(int n) {
	return *this = *this^n;
}

bool Matrice::operator==(Matrice M) {

	if(taille() == 0 || M.taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	if(taille() != M.taille()) {
		throw string("Erreur : Tailles differentes");
	}

	bool isEqual = true;

	for(int i = 1 ; i <= taille() ; i++) {
		if((*this)[i] != M[i]) {
			isEqual = false;
		}
	}

	return isEqual;
}

bool Matrice::operator!=(Matrice M) {
	return !(*this==M);
}

Vecteur& Matrice::operator[](int i) {
	if(taille() == 0) {
		throw string("Erreur : matrice non initialisee");
	}
	else if(i > taille() || i < 1) {
		throw string("Erreur : mauvaises coordonnees");
	}

	return tab[i-1];
}




/* methodes extarieurs a la classe Matrice */

Matrice operator*(float k, Matrice M) {
	return M*k;
}

ostream &operator<<( ostream &out, Matrice matrice) {
    out << matrice.toString();
    return out;
}
