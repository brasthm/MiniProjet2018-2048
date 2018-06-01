#ifndef JEU_H
#define JEU_H

#include "grille.h"

/*
Classe : Jeu
R�sum� :  Objet qui va g�rer le tableau de jeu (gestion et affichage)
*/

class Jeu {
	private:
		// Grille de jeu
		Grille grille_;
		// Score actuel
		int score_;

	public:
		// Constructeur par d�fault
		Jeu();
		// Executer la boucle de jeu
		void executer();
		// Verifie si le jouer a perdu
		bool testDefaite();
};

#endif // !JEU_H