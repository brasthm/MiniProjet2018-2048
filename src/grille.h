#ifndef GRILLE_H
#define GRILLE_H

#include "constantes.h"

#include <ctime>
#include <vector>
#include <iostream>

class Grille
{
	private :
		std::vector<std::vector<int>> grille_;
	public:
		Grille();
		void deplacement(Direction dir);
		void afficher();

		void afficheConsole(); // Fonction de test
};

#endif // !GRILLE_H
