#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void main() {
	/*float a = 3;
	float b = 0;
	ofstream flux("fich.txt");
	flux << "Atletico Madrid " << a << "-" << b << " OM";
	flux.close();

	//Lecture
	ifstream flux2("fich.txt");
	string s;
	getline(flux2, s);
	cout << s;*/
	

	
	int a = 15, b = 14, c = 17;
	vector<int> tab;
	tab.push_back(a);
	tab.push_back(b);
	tab.push_back(c);
	ofstream flux("fich.txt");

	if (!flux.is_open())
		cout << "Erreur d'ouverture" << endl;
	else
	{
		int n=3; // nb noyte
		flux << n<<endl; // Ecriture de la taille
		for (int i = 0; i<n; i++)
			flux << tab[i]<<endl; // Ecriture des éléments
		if (flux.fail())
			cout << "Erreur d'ecriture" << endl;
		else
			cout << "Ecriture terminée" << endl;
	}
	flux.close();

	ifstream flux2("fich.txt"); //lecture
	string s;
	getline(flux2, s,'z'); // Il s'arretera quand il croise un z, yen a pas, il affiche toutes les lignes

	cout << s;

	ifstream fich("fich.txt");
	if (!fich.is_open()) 
		cout << "Erreur d'ouverture" << endl;
	else
	{
	int n;
	fich >> n; // Lecture de la taille
	for (int i = 0; i<n; i++)
	fich >> tab[i]; // Lecture des éléments
	if (fich.fail()) 
		cout << "Erreur de lecture" << endl;

	}
	int stop;
	cin >> stop;
	
}