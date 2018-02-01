#ifndef INTERPRETATION_H
#define INTERPRETATION_H

	#include <string>
	#include <map>

	#include "Matrice.h"
    #include "Vecteur.h"

	enum Type {typeMatrice, typeVecteur, typeNombre, innexistant, invalide};

	void erreur(int numLigne, std::string erreur);
	void erreur(int numLigne);

	int chercherEgal(std::string ligne);

	Type trouverTypeNom(std::string nom, std::map<std::string, Matrice> matrices, std::map<std::string, Vecteur> vecteurs, std::map<std::string, float> nombres);
	bool nomValide(std::string nom);

	Type trouverTypeValeur(std::string valeur);
	bool matriceValide(std::string matrice);
	bool vecteurValide(std::string vecteur);
	bool nombreValide(std::string nombre);

    int tailleMatrice(std::string matrice);
    int tailleVecteur(std::string vecteur);

    Matrice stringToMatrice(std::string matrice);
    Vecteur stringToVecteur(std::string vecteur);

#endif
