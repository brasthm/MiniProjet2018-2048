#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void main() {
	
	
	ifstream fich("fiche.txt");
	if (!fich.is_open())
		cout << "Erreur d'ouverture" << endl; ifstream flux("fich.txt");
	string s;

	getline(flux, s, 'z'); // Il s'arretera quand il croise un z, yen a pas, il affiche toutes les lignes
	flux.close();
	cout << s;

	ifstream fich("fich.txt");
	if (!fich.is_open())
		cout << "Erreur d'ouverture" << endl;
	else
	{
		int n;
		fich >> n; // Lecture de la taille
		vector<int> tab(n);
		for (int i = 0; i<n; i++)
			fich >> tab[i]; // Lecture des éléments
		if (fich.fail())
			cout << "Erreur de lecture" << endl; // Fait une erreur de lecture, si un char est présent au lieu d'un int

	}
	int a;
	cin >> a;
}