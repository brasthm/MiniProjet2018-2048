#include "grille.h"

Grille::Grille()
{
	// Position de la grille dans l'ecran
	pos_x_ = 100;
	pos_y_ = 100;


	// Création de la grille
	for (size_t i = 0; i < TAILLE; i++)
	{
		// Création de la ligne
		grille_.emplace_back();
		for (size_t j = 0; j < TAILLE; j++)
			// Ajout de la colonne
			grille_.back().push_back(0);
	}

	for (size_t i = 0; i < NB_CASE_INIT; i++)
	{
		size_t x, y;

		// Selection d'une case aléatoire VIDE
		do
		{
			x = rand() % TAILLE;
			y = rand() % TAILLE;
		} while (grille_[x][y] != 0);

		// Une chance d'avoir un 4 au lien d'un 2
		grille_[x][y] = rand() % 100 < TAUX_APPARITION_4 ? 4 : 2;
	}

	// Création de l'image grille
	img_grille_.assign(BLOC_W*TAILLE+1, BLOC_H*TAILLE +1, 1, 3, 255);

	for (size_t i = 0; i < TAILLE + 1; i++) img_grille_.draw_line(0, BLOC_H * i, BLOC_H * TAILLE, BLOC_H * i, NOIR);
	for (size_t j = 0; j < TAILLE + 1; j++) img_grille_.draw_line(BLOC_W * j, 0, BLOC_W * j, BLOC_W * TAILLE, NOIR);

	// Création des images blocs

	for (size_t i = 0; i < log2(VALEUR_MAX); i++)
	{
		char c[3] = { 200, 200 - 15 * i, 0 }; //initialisation des couleurs des blocs
		img_blocs_.emplace_back(1, 1, 1, 3, c[0], c[1], c[2]); //création d'un pixel

		cimg_library::CImg<unsigned char> imgtext; //création d'un faux texte pour connaitre la largeur du bloc
		imgtext.draw_text(0, 25, "%d", BLANC, 0, 1, 50, (int)pow(2, i + 1)); // Position du texte à l'intérieur des blocs

		img_blocs_.back().resize(BLOC_W - 1, BLOC_H - 1); //Agrandissement de l'image (ajout de pixel) 
		//recentrage du texte grâce aux infos récoltées
		img_blocs_.back().draw_text(BLOC_W / 2 - imgtext.width()/2, BLOC_W / 2 - imgtext.height() / 2, "%d", BLANC, c, 1, 50, (int)pow(2, i + 1));
	}
}

void Grille::afficher(cimg_library::CImg<unsigned char>& scene)
{
	scene.draw_image(pos_x_, pos_y_, img_grille_);

	for (size_t i = 0; i < TAILLE; i++)
	{
		for (size_t j = 0; j < TAILLE; j++)
		{
			if(grille_[i][j] != 0)
				scene.draw_image(pos_x_ + i * BLOC_W + 1, pos_y_ + j * BLOC_H + 1, img_blocs_[(int)log2(grille_[i][j]) - 1]);
		}
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

void Grille::initTestCouleurs()
{
	grille_[0][0] = 2;
	grille_[0][1] = 4;
	grille_[0][2] = 8;
	grille_[0][3] = 16;
	grille_[1][0] = 32;
	grille_[1][1] = 64;
	grille_[1][2] = 128;
	grille_[1][3] = 256;
	grille_[2][0] = 512;
	grille_[2][1] = 1024;
	grille_[2][2] = 2048;
}
