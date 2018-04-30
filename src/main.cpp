#include "grille.h"
#include "CImg.h"
#include "jeu.h"

#include <ctime>

int main()
{
	srand(time(NULL));

	//Code à mettre dans jeu.cpp

	Grille g;
	Jeu Game;
	Game.executer();

	g.initTestCouleurs();

	// Creation de l'image affiché dans la fenetre
	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	// Création de la fenetre
	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");

	while (!disp.is_closed())
	{
		scene.display(disp);

		// On efface la scene
		scene.fill(255);
		g.afficher(scene);

		disp.wait();
		if (disp.is_resized()) disp.resize();
	}

	return 0;
}