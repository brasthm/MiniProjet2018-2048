#ifndef JEU_H
#define JEU_H

// CLasse .h
#include "grille.h"
class Jeu {
private:
	Grille grille_;
	int score_;
	double temps_;

public:
	Jeu();
	void executer();
};

#endif // !JEU_H