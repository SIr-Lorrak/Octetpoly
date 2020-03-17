#include "Jeu.h"

Jeu::sauver(const string & file) const
{
	ofstream fichier(file.c_str());
	assert(fichier.is_open());
	
	
	fichier.close();
}

Jeu::charger(const string & file)
{
	ifstream fichier(file.c_str());
	assert(fichier.is_open());
	
	
	fichier.close();
}