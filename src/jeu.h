#ifndef JEU_H
#define JEU_H

#include "grille.h"

/*
Classe : Jeu
Résumé :  Objet qui va gérer le tableau de jeu (gestion et affichage)
*/

class Jeu {
	private:
		// Grille de jeu
		Grille grille_;
		// Score actuel
		int score_;

	public:
		// Constructeur par défault
		Jeu();
		// Executer la boucle de jeu
		void executer();
		// Verifie si le jouer a perdu
		bool testDefaite();
};

#endif // !JEU_H