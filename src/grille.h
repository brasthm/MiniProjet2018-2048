#ifndef GRILLE_H
#define GRILLE_H

#include "constantes.h"
#include "CImg.h"

#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>

class Grille
{
	private :
		size_t pos_x_, pos_y_;

		cimg_library::CImg<unsigned char> img_grille_;
		std::vector<cimg_library::CImg<unsigned char>> img_blocs_;

		std::vector<std::vector<int>> grille_;
		
	public:
		Grille();
		int deplacement(Direction dir);
		void afficher(cimg_library::CImg<unsigned char> &scene);
		void create();

		void afficheConsole(); // Fonction de test
		void initTestCouleurs();
};

#endif // !GRILLE_H
