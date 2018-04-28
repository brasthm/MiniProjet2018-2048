#include "grille.h"

#include <ctime>

int main()
{
	srand(time(NULL));

	Grille g;
	g.afficheConsole();
	system("pause");

	return 0;
}