#include "Jeu.h"
#include "grille.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


Jeu::Jeu() {
	score_ = 0;
	temps_ = 0;
}
void Jeu::executer()
{
	grille_;
	//grille_.initTestCouleurs();

	// Creation de l'image affiché dans la fenetre
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	

	// Création de la fenetre
	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");
	bool keyboard = false;

	scene.display(disp);
	scene.fill(255);
	grille_.afficher(scene);
	grille_.loadGame(score_);
	while (!disp.is_closed())
	{
		
		scene.display(disp);
		//______________________________________________
		// On fait des tests pour détecter l'appui sur une touche du clavier (ici flèche haut, bas, droite gauche)
		if (disp.is_keyARROWUP()&& keyboard==false) {
			grille_.deplacement(HAUT, score_);
			grille_.create();
			keyboard = true;
		}
		else if (disp.is_keyARROWDOWN() && keyboard == false) { //l'entrée du clavier est interrogée pour empecher de rester appuyer sur une touche
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
		//Si aucune touche n'est enfoncée on repasse l'entrée à 0
		else if(!disp.is_keyARROWLEFT()&& !disp.is_keyARROWRIGHT()&& !disp.is_keyARROWDOWN()&& !disp.is_keyARROWUP())
		{
			keyboard = false;
		}
		//_____________________________________________

		if (testDefaite()) std::cout << "Defaite" << std::endl;

		// On efface la scene
		scene.fill(255);
		grille_.afficher(scene);
		scene.draw_text(0, 0, "Score : %d", NOIR, 0, 1, 50, score_); // Affichage score
		
		
		


		//disp.wait();
		if (disp.is_resized()) disp.resize();
		

	}
	grille_.saveGame(score_);
	
	
	
}

bool Jeu::testDefaite()
{
	if (grille_.isLibresEmpty())
	{
		int score = 0;
		Grille temp;
		bool defaite = true;

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

