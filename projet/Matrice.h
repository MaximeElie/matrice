#ifndef MATRICE_H
#define MATRICE_H

	#include <vector>

	#include "Vecteur.h"

	using namespace std;

	class Matrice {

		private:

		vector<Vecteur> tab;

		public:

		/* Constructeurs */
		Matrice();
		Matrice(vector<Vecteur> tab);

		/* methodes statiques */
		static Matrice matriceNulle(int taille);
		static Matrice matriceIdentite(int taille);
		static Matrice saisir();

		/* methodes utiles */
		std::string toString();
		int taille();

		/* Getters et setters */
		Vecteur getLigne(int i);
		void setLigne(int i, Vecteur ligne);
		Vecteur getColonne(int j);
		void setColonne(int j, Vecteur colonne);

		/* Opérations avancées */
		float mineur(int i, int j);
		float cofacteur(int i, int j);
		float determinant();
		Matrice comatrice();
		Matrice transpose();
		Matrice inverse();

		/* Surcharge d'operateur */
		Matrice operator+(Matrice M);
		Matrice operator+=(Matrice M);
		Matrice operator-(Matrice M);
		Matrice operator-=(Matrice M);
		Matrice operator*(Matrice M);
		Matrice operator*=(Matrice M);
		Matrice operator*(float k);
		Matrice operator*=(float k);
		Matrice operator^(int n);
		Matrice operator^=(int n);
		bool operator==(Matrice M);
		bool operator!=(Matrice M);
		Vecteur& operator[](int i);
	};

	/* methodes extarieurs a la classe Matrice */
	Matrice operator*(float k, Matrice M);
	ostream &operator<<( ostream &out, Matrice matrice);

#endif
