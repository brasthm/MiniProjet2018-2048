#include "Jeu.h"
#include "grille.h"


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

	Sleep(1000);

	while (!disp.is_closed())
	{

		grille_.deplacement(BAS);
		grille_.create();
		Sleep(500);

		scene.display(disp);

		// On efface la scene
		scene.fill(255);
		grille_.afficher(scene);

		//disp.wait();
		if (disp.is_resized()) disp.resize();
	}
}
