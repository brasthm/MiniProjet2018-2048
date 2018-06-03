#include "grille.h"
#include <fstream>
#include <iostream>

void HSV2RGB(char *c, float c1, float c2, float c3)
{
	int mod = (int)floor(c1 / 60) % 6;

	float f = c1/60. - mod;

	float l = c3 * (1 - c2);
	float m = c3 * (1 - f*c2);
	float n = c3 * (1 - (1-f)*c2);

	switch (mod)
	{
		case 0:
			c[0] = c3 * 256;
			c[1] = n * 256;
			c[2] = l * 256;
			break;
		case 1:
			c[0] = m * 256;
			c[1] = c3 * 256;
			c[2] = l * 256;
			break;
		case 2:
			c[0] = l * 256;
			c[1] = c3 * 256;
			c[2] = n * 256;
			break;
		case 3:
			c[0] = l * 256;
			c[1] = m * 256;
			c[2] = c3 * 256;
			break;
		case 4:
			c[0] = n * 256;
			c[1] = l * 256;
			c[2] = c3 * 256;
			break;
		case 5:
			c[0] = c3 * 256;
			c[1] = l * 256;
			c[2] = m * 256;
			break;
	}
}

Grille::Grille()
{
	// Position de la grille dans l'ecran
	pos_x_ = 200;
	pos_y_ = 100;


	// Cr�ation de la grille
	for (size_t i = 0; i < TAILLE; i++)
	{
		// Cr�ation de la ligne
		grille_.emplace_back();
		for (size_t j = 0; j < TAILLE; j++)
			// Ajout de la colonne
			grille_.back().push_back(0);
	}

	// Placement des blocs de d�part
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

	// Cr�ation de l'image grille
	img_grille_.assign(BLOC_W*TAILLE+1, BLOC_H*TAILLE +1, 1, 3, 255);

	for (size_t i = 0; i < TAILLE + 1; i++) img_grille_.draw_line(0, BLOC_H * i, BLOC_H * TAILLE, BLOC_H * i, NOIR);
	for (size_t j = 0; j < TAILLE + 1; j++) img_grille_.draw_line(BLOC_W * j, 0, BLOC_W * j, BLOC_W * TAILLE, NOIR);

	// Cr�ation des images blocs

	for (size_t i = 0; i < log2(VALEUR_MAX); i++)
	{
		char c[3]; //initialisation des couleurs des blocs
		HSV2RGB(c, 2*i*360./log2(VALEUR_MAX), 1, 0.7); //color
		img_blocs_.emplace_back(1, 1, 1, 3, c[0], c[1], c[2]); //cr�ation d'un pixel

		cimg_library::CImg<unsigned char> imgtext; //cr�ation d'un texte tampon pour connaitre la largeur du bloc
		imgtext.draw_text(0, 0, "%d", BLANC, 0, 1, 50, (int)pow(2, i + 1)); // Position du texte � l'int�rieur des blocs


		img_blocs_.back().resize(BLOC_W - 1, BLOC_H - 1); //Agrandissement de l'image (ajout de pixel) 
		//recentrage du texte gr�ce aux infos r�colt�es
		img_blocs_.back().draw_text(BLOC_W / 2 - imgtext.width()/2, BLOC_W / 2 - imgtext.height() / 2, "%d", BLANC, c, 1, 50, (int)pow(2, i + 1));
	}
}

/*
Auteur : Cyril Li
Description : Gere le d�placement des blocs
Param�tres : dir -> Direction du d�placement
			 score -> Score actuel
Retour : Vrai si on a d�plac� une case, faux sinon
*/
bool Grille::deplacement(Direction dir, int &score)
{
	// Bol�en indiquant si on on a boug� une case
	bool moved = false;

	// Test de la direction
	switch (dir)
	{
		// D�placement vers le haut
		case HAUT:
			// Parcours de toutes les lignes
			for (int i = 0; i < TAILLE; i++)
			{
				// Parcours de toutes les colones (sauf la premi�re)
				for (int j = 1; j < TAILLE; j++)
				{
					// Si la case n'est pas vide
					if (grille_[i][j] != 0)
					{
						// Parcours de la case du dessus jusqu'au bord sup�rieur
						for (int k = j - 1; k >= 0; k--)
						{
							// Si la case est vide
							if (grille_[i][k] == 0)
							{
								// D�placement
								grille_[i][k] = grille_[i][k + 1];
								grille_[i][k + 1] = 0;
								moved = true;
							}
							// Si la case a une valeur identique � la case de d�part
							else if (grille_[i][k] == grille_[i][k + 1])
							{
								// Addition des scores
								grille_[i][k] = 2 * grille_[i][k + 1];
								score += grille_[i][k + 1];
								grille_[i][k + 1] = 0;
								moved = true;
								// On a termier le d�placement de cette case
								break;
							}
							// Sinon, on a une case d'une valeur diff�rente : on ne bouge plus la case
							else break;
						}
					}
				}
			}
			break;
		// D�placement vers le bas
		case BAS:
			for (int i = 0; i < TAILLE; i++)
			{
				for (int j = TAILLE - 2; j >= 0; j--)
				{
					if (grille_[i][j] != 0)
					{
						for (int k = j + 1; k < TAILLE; k++)
						{
							if (grille_[i][k] == 0)
							{
								grille_[i][k] = grille_[i][k - 1];
								grille_[i][k - 1] = 0;
								moved = true;
							}
							else if (grille_[i][k] == grille_[i][k - 1])
							{
								grille_[i][k] = 2 * grille_[i][k - 1];
								score += grille_[i][k - 1];
								grille_[i][k - 1] = 0;
								moved = true;
								break;
							}
							else break;
						}
					}
				}
			}
			break;
		// D�placement vers la droite
		case DROITE:
			for (int i = TAILLE - 2; i >= 0; i--)
			{
				for (int j = 0; j < TAILLE; j++)
				{
					if (grille_[i][j] != 0)
					{
						for (int k = i + 1; k < TAILLE; k++)
						{
							if (grille_[k][j] == 0)
							{
								grille_[k][j] = grille_[k - 1][j];
								grille_[k - 1][j] = 0;
								moved = true;
							}
							else if (grille_[k][j] == grille_[k - 1][j])
							{
								grille_[k][j] = 2 * grille_[k - 1][j];
								score += grille_[k - 1][j];
								grille_[k - 1][j] = 0;
								moved = true;
								break;
							}
							else break;
						}
					}
				}
			}
			break;
		// D�placement vers la gauche
		case GAUCHE:
			for (int i = 1; i < TAILLE; i++)
			{
				for (int j = 0; j < TAILLE; j++)
				{
					if (grille_[i][j] != 0)
					{
						for (int k = i-1; k >= 0; k--)
						{
							if (grille_[k][j] == 0)
							{
								grille_[k][j] = grille_[k + 1][j];
								grille_[k + 1][j] = 0;
								moved = true;
							}
							else if (grille_[k][j] == grille_[k + 1][j])
							{
								grille_[k][j] = 2 * grille_[k + 1][j];
								score += grille_[k + 1][j];
								grille_[k + 1][j] = 0;
								moved = true;
								break;
							}
							else break;
						}
					}
				}
			}
			break;
		default:
			break;
	}

	return moved;
}

/*
Auteur : Cyril Li
Description : Affiche la grille
Param�tres : score -> Score actuel
Retour : /
*/
void Grille::afficher(cimg_library::CImg<unsigned char>& scene)
{
	// Affichage de la grille
	scene.draw_image(pos_x_, pos_y_, img_grille_);

	// Parcours de la grile
	for (size_t i = 0; i < TAILLE; i++)
	{
		for (size_t j = 0; j < TAILLE; j++)
		{
			// Si la case n'est pas vide
			if(grille_[i][j] != 0)
				// Affichage � la bonne position du bloc correscpondant
				scene.draw_image(pos_x_ + i * BLOC_W + 1, pos_y_ + j * BLOC_H + 1, img_blocs_[(int)log2(grille_[i][j]) - 1]);
		}
	}
}

/*
Auteur : Cyril Li
Description : Cr�ation de blocs � des emplacements al�atoire
Param�tres : /
Retour : /
*/
void Grille::create()
{
	// Mise � jour des emplacement libres
	check_libre();

	// On r�pete un nombre de fois choisi
	for (size_t i = 0; i < NB_CASE_INIT; i++)
	{
		// S'il reste des emplacements vide
		if (!libres_.empty())
		{
			size_t x, y;

			// Selection d'une case al�atoire VIDE
			size_t n = rand() % libres_.size();
			x = libres_[n].first;
			y = libres_[n].second;

			// Une chance d'avoir un 4 au lien d'un 2
			grille_[x][y] = rand() % 100 < TAUX_APPARITION_4 ? 4 : 2;
		}
		
	}

	// Mise � jour des emplacement libres
	check_libre();
}

/*
Auteur : Cyril Li
Description : Met � jour le vecteur des cases vide
Param�tres : /
Retour : /
*/
void Grille::check_libre()
{
	// On efface le vecteur
	libres_.clear();

	// Parcours de la grille
	for (size_t i = 0; i < TAILLE; i++)
		for (size_t j = 0; j < TAILLE; j++)
			// Si on a une case vide,  on rajoute la case dans le vecteur des emplacements libres
			if (grille_[i][j] == 0)
				libres_.emplace_back(i, j);

}
/*
Auteur : Adrien Lebron
Description : Sauvegarde la partie dans un fichier texte 
Param�tres : Score de la partie
Retour : /
*/
void Grille::saveGame(int score){
	std::ofstream save("savedgame.txt"); //Ouverture du fichier txt
	save << score << std::endl; //Ecriture du score sur la premi�re ligne
	for (int i = 0; i < grille_.size(); i++) {

		for (int j = 0; j < grille_[0].size(); j++) { //Parcours de la grille
			
			save << grille_[j][i] << " ";// Sauvegarde d'une ligne enti�re
		}
		save<<std::endl;
	}
}
/*
Auteur : Adrien Lebron
Description : Charge une partie sauvegard�
Param�tres : Le score
Retour : /
*/
void Grille::loadGame(int &score) {
	std::ifstream load("savedgame.txt"); //Ouvre le fichier de sauvegarde
	load >> score; // R�cup�re le score
	for (int i = 0; i < grille_.size(); i++) {
		for (int j = 0; j < grille_[0].size(); j++) {
			load >> grille_[j][i]; //R�cup�re une � une les cases de la grille et leurs valeurs
		}
	}
	check_libre(); //Va ajourner le vecteur des cases libres
}
/*
Auteur : Adrien Lebron
Description : R�initialise la grille pour d�marer une nouvelle partie
Param�tres : /
Retour : /
*/
void Grille::reinitialiserGrille(int &score) {
	for (int i = 0; i < grille_.size(); i++) {
		for (int j = 0; j < grille_[0].size(); j++) { //Parcours de la grille
			grille_[j][i] = 0;			// REmise � 0
		}
	}
	score = 0;
	create(); // Met deux cases � 2 ou 4 al�atoirement
}
/*
Auteur : Adrien Lebron
Description : Teste la victoire (affichage d'une case � 2048)
Param�tres : /
Retour : Bool�en � vrai si le joueur a gagn�, faux sinon
*/
bool Grille::testVictoire() {
	for (int i = 0; i < grille_.size(); i++) {
		for (int j = 0; j < grille_[0].size(); j++) {//Parcours de la grille
			if (grille_[j][i] == 2048) //Test sur chaque case
				return true;
		}
	}
	return false;
}
