#include "grille.h"
#include "CImg.h"

#include <ctime>

int main()
{
	srand(time(NULL));

	//Code à mettre dans jeu.cpp

	Grille g;

	cimg_library::CImg<unsigned char> scene(ECRAN_W, ECRAN_H, 1, 3, 255);

	cimg_library::CImgDisplay disp(ECRAN_W, ECRAN_H, "2048");

	while (!disp.is_closed())
	{
		scene.display(disp);

		disp.wait();
		if (disp.is_resized()) disp.resize();
	}

	return 0;
}