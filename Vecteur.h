#ifndef VECTEUR_H
#define VECTEUR_H

	#include <vector>
	#include <string>

	using namespace std;

	class Vecteur {
		private:
		
		vector<float> tab;
		
		public:
		
		/* Constructeurs */		
		Vecteur();
		Vecteur(vector<float> tab);
		
		/* methodes statiques */
		static Vecteur vecteurNul(int taille);
		
		/* Getters et setters */
		int taille();
		float scalaire(int i);
		float setScalaire(int i, float valeur);
		
		/* Surcharge d'operateur */
		Vecteur operator+(Vecteur V);	
		Vecteur operator+=(Vecteur V);
		Vecteur operator-(Vecteur V);	
		Vecteur operator-=(Vecteur V);	
		Vecteur operator*(float k);	
		Vecteur operator*=(float k);	
		bool operator==(Vecteur V);
		bool operator!=(Vecteur V);
	};

	/* methodes extarieurs a la classe Matrice */
	Vecteur operator*(float k, Vecteur V);

#endif
