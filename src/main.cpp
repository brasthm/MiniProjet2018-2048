#include "grille.h"

#include <ctime>

int main()
{
	srand(time(NULL));

	while (1)
	{
		Grille g;
		g.afficheConsole();
		system("pause");
	}
	


	return 0;
}