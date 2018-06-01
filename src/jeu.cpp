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
Param�tres : /
Retour : /
*/
Jeu::Jeu() {
	score_ = 0;
}

/*
Auteur : Adrien Lebron
Description : Executer la boucle de jeu
Param�tres : /
Retour : /
*/
void Jeu::executer()
{
	// Creation de l'image affich� dans la fenetre
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	// Cr�ation de la fenetre
	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");
	bool keyboard = false;

	grille_.loadGame(score_);

	scene.display(disp);
	scene.fill(255);
	grille_.afficher(scene);
	
	while (!disp.is_closed())
	{
		
		scene.display(disp);
		//______________________________________________
		// On fait des tests pour d�tecter l'appui sur une touche du clavier (ici fl�che haut, bas, droite gauche)
		if (disp.is_keyARROWUP()&& keyboard==false) {
			grille_.deplacement(HAUT, score_);
			grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWDOWN() && keyboard == false) { //l'entr�e du clavier est interrog�e pour empecher de rester appuyer sur une touche
			grille_.deplacement(BAS, score_);
			grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWRIGHT() && keyboard == false) {
			grille_.deplacement(DROITE, score_);
			grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWLEFT() && keyboard == false) {
			grille_.deplacement(GAUCHE, score_);
			grille_.create();
			keyboard = true;
		}
		//Si aucune touche n'est enfonc�e on repasse l'entr�e � 0
		else if(!disp.is_keyARROWLEFT()&& !disp.is_keyARROWRIGHT()&& !disp.is_keyARROWDOWN()&& !disp.is_keyARROWUP())
		{
			keyboard = false;
		}
		if (disp.is_keyR()) {
			grille_.reinitialiserGrille(score_);
		}
		//_____________________________________________
		
		if (testDefaite()) {
			
			std::cout << "Defaite" << std::endl;
		
				endDisplay("D�faite", scene, disp);
				
			
		}

		if (grille_.testVictoire()) std::cout << "Victoire" << std::endl;
		// On efface la scene
		scene.fill(255);
		grille_.afficher(scene);
		int highscore;
		std::ifstream high("highscore.txt");
		high >> highscore;
		scene.draw_text(0, 0, "Score : %d", NOIR, 0, 1, 50, score_); // Affichage score
		scene.draw_text(0, 520, "Appuyer sur R pour commencer une nouvelle partie", NOIR, 0, 1, 20); // Affichage score
		scene.draw_text(530, 0, "Highscore : %d", NOIR, 0, 1, 40,highscore); // Affichage score
		


		//disp.wait();
		if (disp.is_resized()) disp.resize();
	}
	grille_.saveGame(score_);
	
	
	
}

/*
Auteur : Adrien Lebron
Description : Determine si le joueur a perdu
Param�tres : /
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

		// On teste le d�placement sur la grille temporaire : si on arrive � bouger, defaite passe � False
		// Si on n'arrive pas � bouger dans les 4 direction, defaite reste � Vrai et on a d�tecter la victoire


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
void Jeu::endDisplay(std::string s, cimg_library::CImg<unsigned char> &lastscreen, cimg_library::CImgDisplay &disp) {
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255); //cr�ationd e l'�cran vierge
	while(!disp.is_keyR())
	{
		scene.display(disp);
		scene.draw_image(lastscreen);
		scene.draw_rectangle(0, 0, ECRAN_W, ECRAN_H, NOIR, 0.5);
		scene.draw_text(250, 150, " %s", BLANC, 0, 1, 50, s.c_str());
	}
}

