#include "Jeu.h"
#include "grille.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*
Auteur : Cyril Li
Description : Contructeur du jeu
Paramètres : /
Retour : /
*/
Jeu::Jeu() {
	score_ = 0;
}

/*
Auteur : Adrien Lebron
Description : Executer la boucle de jeu
Paramètres : /
Retour : /
*/
void Jeu::executer()
{
	bool continuer = true;
	bool victoire = false;

	// Creation de l'image affiché dans la fenetre
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	// Création de la fenetre
	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");

	bool keyboard = false;

	init();
	grille_.loadGame(score_);


	while (!disp.is_closed() && continuer)
	{
		bool moved;
		
		//______________________________________________
		// On fait des tests pour détecter l'appui sur une touche du clavier (ici flèche haut, bas, droite gauche)
		if (disp.is_keyARROWUP()&& keyboard==false) {
			moved = grille_.deplacement(HAUT, score_);
			if(moved) grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWDOWN() && keyboard == false) { //l'entrée du clavier est interrogée pour empecher de rester appuyer sur une touche
			moved = grille_.deplacement(BAS, score_);
			if (moved) grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWRIGHT() && keyboard == false) {
			moved = grille_.deplacement(DROITE, score_);
			if (moved) grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWLEFT() && keyboard == false) {
			moved = grille_.deplacement(GAUCHE, score_);
			if (moved) grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyR() && keyboard == false) {
			init();
			keyboard = true;
		}
		//Si aucune touche n'est enfoncée on repasse l'entrée à 0
		else if(!disp.is_keyARROWLEFT()&& !disp.is_keyARROWRIGHT()&& !disp.is_keyARROWDOWN()&& !disp.is_keyARROWUP() && !disp.is_keyR())
		{
			keyboard = false;
		}
		
		//_____________________________________________
		
		// On efface la scene
		scene.fill(255);
		grille_.afficher(scene);

		if (testDefaite()) {
			continuer = endDisplay("Défaite", scene, disp);
			init();
		}

		if (!victoire && grille_.testVictoire())
		{
			continuer = endDisplay("Victoire", scene, disp);
			victoire = true;
		}
		
		scene.draw_text(0, 0, "Score : %d", NOIR, 0, 1, 50, score_); // Affichage score
		scene.draw_text(0, 580, "Appuyer sur R pour commencer une nouvelle partie", NOIR, 0, 1, 20); // Affichage score
		scene.draw_text(510, 0, "Highscore : %d", NOIR, 0, 1, 40, score_ > highscore_ ? score_ : highscore_); // Affichage score

		//disp.wait();
		if (disp.is_resized()) disp.resize();

		scene.display(disp);
	}

	grille_.saveGame(score_);
}

/*
Auteur : Cyril Li
Description : Determine si le joueur a perdu
Paramètres : /
Retour : Vrai si le joueur a perdu, faux sinon
*/
bool Jeu::testDefaite()
{
	// Si il n'y a plus de de cases libre
	if (grille_.isLibresEmpty())
	{
		// Score tampon
		int score = 0;
		// Grille temporaire
		Grille temp;
		bool defaite = true;

		// On teste le déplacement sur la grille temporaire : si on arrive à bouger, defaite passe à False
		// Si on n'arrive pas à bouger dans les 4 direction, defaite reste à Vrai et on a détecter la victoire


		temp = grille_;
		defaite = defaite && !temp.deplacement(HAUT, score);

		temp = grille_;
		defaite = defaite && !temp.deplacement(BAS, score);

		temp = grille_;
		defaite = defaite && !temp.deplacement(DROITE, score);

		temp = grille_;
		defaite = defaite && !temp.deplacement(GAUCHE, score);

		return defaite;
	}
	else return false;
}
/*
Auteur : Adrien Lebron
Description : Création de l'affichage de fin de partie
Paramètres : String avec le message Victoire ou défait à afficher, le dernier écran (la grille) et notre affichage
Retour : /
*/

bool Jeu::endDisplay(std::string s, cimg_library::CImg<unsigned char> &lastscreen, cimg_library::CImgDisplay &disp) {
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255); //créationd e l'écran vierge

	cimg_library::CImg<unsigned char> imgtext; //création d'un texte tampon pour connaitre la largeur du bloc
	
	scene.draw_image(lastscreen); //Récupération de l'ancien écran
	scene.draw_rectangle(0, 0, ECRAN_W, ECRAN_H, NOIR, 0.5); // Dessin d'un rectangle par dessus

	imgtext.draw_text(0, 0, "%s", BLANC, 0, 1, 75, s.c_str());
	scene.draw_text((ECRAN_W - imgtext.width()) / 2, 10, "%s", BLANC, 0, 1, 75, s.c_str()); // Affichage victoire ou défaite

	imgtext.clear();
	imgtext.draw_text(0, 0, "Score : %d", BLANC, 0, 1, 75, score_);
	scene.draw_text((ECRAN_W - imgtext.width()) / 2, 200, "Score : %d", BLANC, 0, 1, 75, score_);// Affichage score

	scene.draw_text(0, 580, "Appuyer sur R pour commencer une nouvelle partie", BLANC, 0, 1, 20); // Affichage Reset

	drawHighscore(scene);

	scene.display(disp);
	while(true) {
		if (disp.is_keyR())
			return true;
		if (disp.is_closed())
			return false;

		disp.wait();
	}
}
/*
Auteur : Adrien Lebron
Description : Récupération des highscore dans un fichier txt
Paramètres : Vecteur d'entier contenant les scores
Retour : /
*/
void Jeu::getScoreList(std::vector<int> &highscore)
{
	std::ifstream resultat("highscore.txt"); //Récupération de l'ancien fichier d'highscore
	if (resultat.is_open())
	{
		
		std::string ligne;

		while (std::getline(resultat, ligne)) { //Tant qu'on peux lire des lignes dans le fichier
			highscore.push_back(std::stoi(ligne));// On convertit ligne en entier
		}

		highscore.push_back(score_);//ajout à la fin du dernier score enregistrée
		std::sort(highscore.rbegin(), highscore.rend()); // Tri par ordre décroissant

		resultat.close();
	}
}
/*
Auteur : Adrien Lebron
Description : Sauvegarde du score dans le fichier txt
Paramètres : /
Retour : /
*/
void Jeu::saveScore()
{
	if (score_ != 0)
	{
		std::vector <int> highscore;
		getScoreList(highscore); // Récupération des highscore

		std::ofstream flux("highscore.txt", std::ios::out | std::ios::trunc);
		for (int i = 0; i < highscore.size(); i++) {
			flux << highscore[i] << std::endl; //Ecriture des scores dans le fichier
		}
	}
}
// Lire les highscores Adrien LEBRON

void Jeu::readHighscore()
{
	std::ifstream high;

	high.open("highscore.txt", std::ios::in); //Ouverture des highscore

	while (!high)
	{
		std::ofstream save("highscore.txt", std::ios::out | std::ios::trunc);
		save << "0";
		save.close();
		high.open("highscore.txt", std::ios::in);
	}

	high >> highscore_;
	high.close();

}
/*
Auteur : Adrien Lebron
Description : Initialisation d'une partie
Paramètres : /
Retour : /
*/
void Jeu::init()
{
	saveScore(); //Sauvegarde le score
	grille_.reinitialiserGrille(score_); //Relance la grille à 0
	readHighscore();
}
/*
Auteur : Adrien Lebron
Description : Dessine les scores en fin de partie
Paramètres : La scène actuelle
Retour : /
*/

void Jeu::drawHighscore(cimg_library::CImg<unsigned char> &scene)
{
	std::vector <int> highscore;
	getScoreList(highscore);

	cimg_library::CImg<unsigned char> imgtext; //création d'un texte tampon pour connaitre la largeur du bloc
	
	int i = 0;
	while (i < 3 && i < highscore.size())
	{
		imgtext.clear();
		imgtext.draw_text(0, 0, "%d - %d", BLANC, 0, 1, 70, i+1, highscore[i]);// Affichage score
		scene.draw_text((ECRAN_W - imgtext.width()) / 2, 300 + 75*i, "%d - %d", BLANC, 0, 1, 75, i + 1, highscore[i]);
		i++;
	}

}