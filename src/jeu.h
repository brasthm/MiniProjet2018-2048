#ifndef JEU_H
#define JEU_H

#include "grille.h"

/*
Classe : Jeu
Résumé :  Objet qui va gérer le tableau de jeu (gestion et affichage)
*/

class Jeu {
	private:
		// Grille de jeu
		Grille grille_;
		// Score actuel
		int score_;
		int highscore_;

	public:
		// Constructeur par défault
		Jeu();
		// Executer la boucle de jeu
		void executer();
		// Verifie si le jouer a perdu
		bool testDefaite();
		// Affiche un 
		bool endDisplay(std::string s, cimg_library::CImg<unsigned char> &lastscreen, cimg_library::CImgDisplay &disp);
		// Sauvegarde le score
		void saveScore();
		// Lis les plus gros scores dans un fichier txt
		void readHighscore();
		// Initialise une partie
		void init();
		// Ecris les meilleurs scores à la fin d'une partie
		void drawHighscore(cimg_library::CImg<unsigned char> &scene);
		//Récupère les meilleurs score et les stocke dans un vector
		void getScoreList(std::vector<int> &highscore);
		
};

#endif // !JEU_H