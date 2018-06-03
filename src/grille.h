#ifndef GRILLE_H
#define GRILLE_H

#include "constantes.h"
#include "CImg.h"

#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>

/*
	Classe : Grille
	R�sum� :  Objet qui va g�rer le tableau de jeu (gestion et affichage)
*/
class Grille
{
	private :
		// Position dans le fen�tre de la grille
		size_t pos_x_, pos_y_;

		// Image de la grille
		cimg_library::CImg<unsigned char> img_grille_;
		// Images de tout les blocs
		std::vector<cimg_library::CImg<unsigned char>> img_blocs_;

		// Tableau 2 dims contentant l'�tat de la grille
		std::vector<std::vector<int>> grille_;
		// Vecteur de touts les cases vides
		std::vector<std::pair<int, int>> libres_;
		
	public:
		// Constructeur par d�fault
		Grille();
		// G�re le d�placement des blocs
		bool deplacement(Direction dir, int &score);
		// Affiche le tableau
		void afficher(cimg_library::CImg<unsigned char> &scene);
		// Cr�er de nouveau blocs dans la grille
		void create();
		// Recherche toute les instersections libles
		void check_libre();
		// Enregistre la partie � la fermeture de la fen�tre
		void saveGame(int score);
		// Chargement de la partie pr�cedente
		void loadGame(int &score);
		// R�initialise la grille pour une nouvelle partie
		void reinitialiserGrille(int &score);
		//Teste la victoire(affichage d'une case � 2048)
		bool testVictoire();
		// Teste si il reste des case libres
		// Retourne Vrai s'il n'y a plus de de case libre, Retourne Faux sinon
		bool isLibresEmpty() { return libres_.empty(); };

		
};

#endif // !GRILLE_H
