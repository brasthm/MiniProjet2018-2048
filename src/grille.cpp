#include "grille.h"

Grille::Grille()
{
	// Cr�ation de la grille
	for (size_t i = 0; i < TAILLE; i++)
	{
		// Cr�ation de la ligne
		grille_.emplace_back();
		for (size_t j = 0; j < TAILLE; j++)
			// Ajout de la colonne
			grille_.back().push_back(0);
	}

	for (size_t i = 0; i < NB_CASE_INIT; i++)
	{
		size_t x, y;

		// Selection d'une case al�atoire VIDE
		do
		{
			x = rand() % TAILLE;
			y = rand() % TAILLE;
		} while (grille_[x][y] != 0);

		// Une chance d'avoir un 4 au lien d'un 2
		grille_[x][y] = rand() % 100 < TAUX_APPARITION_4 ? 4 : 2;
	}
		
}

void Grille::afficheConsole()
{
	for (size_t i = 0; i < TAILLE; i++)
	{
		for (size_t j = 0; j < TAILLE; j++)
			std::cout << grille_[i][j] << " ";
		std::cout << std::endl;
	}
}
