#include "Carte.h"

//retourne le gain
int Carte::getgain() const{
	return gain;

}


//retourne l'id de la case
int Carte::getid_case() const{
	return id_case;
}

//retourne l'id de la carte
int Carte::getid_carte() const{
	return id_carte;
}

//retourne un bool
bool Carte::getcasePlus3() const{
	return casePlus3;
}

string Carte::getTitre() const{
	return tab_carte[0][id_carte];
}

string Carte::getTexte() const{
	return tab_carte[1][id_carte];
}

//pioche une carte au hasard
void Carte::randomCarte(){

	srand (time(NULL));
	id_carte = rand()%2;
	switch(id_carte){
		case 0:
			id_case = 0;
			gain = 0;
			casePlus3 = false;
			break;

		case 1:
			id_case = -1;
			gain = -500;
			casePlus3 = false;
			break;

		case 2:
			id_case = -1;
			gain = 0;
			casePlus3 = true;
			break;

	}
}