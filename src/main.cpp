#include "grille.h"
#include "CImg.h"
#include "jeu.h"

#include <ctime>

int main()
{
	srand(time(NULL));

	Jeu Game;
	Game.executer();

	return 0;
}