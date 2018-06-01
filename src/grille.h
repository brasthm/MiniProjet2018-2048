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
		std::vector<std::pair<int, int>> libres_;
		
	public:
		Grille();
		bool deplacement(Direction dir, int &score);
		void afficher(cimg_library::CImg<unsigned char> &scene);
		void create();
		void check_libre();
		void afficheConsole(); // Fonction de test
		void initTestCouleurs();
		bool isLibresEmpty() { return libres_.empty(); };
		void saveGame(int score);
		void loadGame(int &score);
		void reinitialiserGrille(int &score);
};

#endif // !GRILLE_H
