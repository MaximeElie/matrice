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
		
		/* Surcharge d'operateur */
		Vecteur operator+(Vecteur V);	
		Vecteur operator+=(Vecteur V);
		Vecteur operator-(Vecteur V);	
		Vecteur operator-=(Vecteur V);	
		Vecteur operator*(float k);	
		Vecteur operator*=(float k);	
		bool operator==(Vecteur V);
		bool operator!=(Vecteur V);
		float& operator[](int i);
	};

	/* methodes extarieurs a la classe Matrice */
	Vecteur operator*(float k, Vecteur V);

#endif
