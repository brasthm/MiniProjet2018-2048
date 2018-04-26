#ifndef GRILLE_H
#define GRILLE_H

#include "constantes.h"

#include <vector>

class Grille
{
	private :

	public:
		Grille();
		void deplacement(Direction dir);
		void afficher();
};

#endif // !GRILLE_H
