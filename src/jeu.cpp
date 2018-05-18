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
	grille_.initTestCouleurs();

	// Creation de l'image affiché dans la fenetre
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	

	// Création de la fenetre
	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");

	while (!disp.is_closed())
	{
		scene.display(disp);

		// On efface la scene
		scene.fill(255);
		grille_.afficher(scene);
		scene.draw_text(0, 0, "Score : %d", NOIR, 0, 1, 50, score_); // Affichage score
		
		
		




		disp.wait();
		if (disp.is_resized()) disp.resize();
	}
	savescore();

}

void Jeu::savescore()
{
	std::ifstream resultat("highscore.txt"); //Récupération de l'ancien fichier d'highscore
	if (!resultat.is_open())
		std::cout << "Erreur d'ouverture" << std::endl;
	std::vector <int> highscore;
	std::string ligne;

	while (std::getline(resultat, ligne)) { //Tant qu'on peux lire des lignes dans le fichier
		highscore.push_back(std::stoi(ligne));// On convertit ligne en entier
	}


	highscore.push_back(score_);//ajout à la fin du dernier score enregistrée
	
	std::sort(highscore.rbegin(), highscore.rend());

	int i = 0;
	for ( i = 0; i <highscore.size(); i++)
		std::cout << highscore[i]<<std::endl;

	std::ofstream flux("highscore.txt", std::ios::out | std::ios::trunc);
	for (int i = 0; i < highscore.size(); i++) {
		flux << highscore[i] << std::endl;
	}
	int stop;
	std::cin >> stop;
}
