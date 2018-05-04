#include "Jeu.h"
#include "grille.h"
#include <iostream>


Jeu::Jeu() {
	score_ = 0;
	temps_ = 0;
}
void Jeu::executer()
{
	grille_;
	grille_.initTestCouleurs();

	// Creation de l'image affiché dans la fenetre
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	// Création de la fenetre
	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");
	bool keyboard = false;
	while (!disp.is_closed())
	{
		scene.display(disp);
		//______________________________________________
		// On fait des tests pour détecter l'appui sur une touche du clavier (ici flèche haut, bas, droite gauche)
		if (disp.is_keyARROWUP()&& keyboard==false) {
			std::cout << "Touche haut detectee" << std::endl;
			keyboard = true;
		}
		else if (disp.is_keyARROWDOWN() && keyboard == false) { //l'entrée du clavier est interrogée pour empecher de rester appuyer sur une touche
			std::cout << "Touche Bas detectee" << std::endl;
			keyboard = true;
		}
		else if (disp.is_keyARROWRIGHT() && keyboard == false) {
			std::cout << "Touche Droite detectee" << std::endl;
			keyboard = true;
		}
		else if (disp.is_keyARROWLEFT() && keyboard == false) {
			std::cout << "Touche Gauche detectee" << std::endl;
			keyboard = true;
		}
		//Si aucune touche n'est enfoncée on repasse l'entrée à 0
		else if(!disp.is_keyARROWLEFT()&& !disp.is_keyARROWRIGHT()&& !disp.is_keyARROWDOWN()&& !disp.is_keyARROWUP())
		{
			keyboard = false;
		}

		
		//_____________________________________________

		// On efface la scene
		scene.fill(255);
		grille_.afficher(scene);

		disp.wait();
		if (disp.is_resized()) 
			disp.resize();
	}
	
}

