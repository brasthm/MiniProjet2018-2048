#ifndef CONSTANTES_H
#define CONSTANTES_H

// -------------- Constantes -------------- //

constexpr size_t TAILLE = 4;
constexpr size_t NB_CASE_INIT = 2;

// Pourcentage de chance de tomber sur un 4 lors de la création d'un bloc
constexpr size_t TAUX_APPARITION_4 = 10; 

// Dimension de l'écran (en px)
constexpr size_t ECRAN_W = 800;
constexpr size_t ECRAN_H = 600;

// Dimmension d'une case (en px)
constexpr size_t BLOC_W = 100;
constexpr size_t BLOC_H = 100;

constexpr size_t VALEUR_MAX = 2048;

// Couleurs
constexpr unsigned char NOIR[3] = { 0, 0, 0 };
constexpr unsigned char BLANC[3] = { 255, 255, 255 };


// ------------ Types énumérés ------------ //
enum Direction {HAUT, BAS, DROITE, GAUCHE};


#endif // CONSTANTES_H