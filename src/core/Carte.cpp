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

	id_carte = 6;//rand()%25;
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

		case 3:
			id_case = 19;
			gain = 0;
			casePlus3 = false;
			break;

		case 4://Carte spéciale
			id_case = -1;
			gain = 0;
			casePlus3 = false;
			break;

		case 5:
			id_case = -1;
			gain = -100;
			casePlus3 = false;
			break;

		case 6:
			id_case = -1;
			gain = 250;
			casePlus3 = false;
			break;

		case 7://Carte spéciale
			id_case = -1;
			gain = 100;
			casePlus3 = false;
			break;

		case 8:
			id_case = -1;
			gain = 200;
			casePlus3 = false;
			break;

		case 9:
			id_case = -1;
			gain = 500;
			casePlus3 = false;
			break;
//--------------------------------------------
		case 10:
			id_case = -1;
			gain = -150;
			casePlus3 = false;
			break;

		case 11:
			id_case = -1;
			gain = -100;
			casePlus3 = false;
			break;

		case 12:
			id_case = -1;
			gain = -400;
			casePlus3 = false;
			break;

		case 13:
			id_case = -1;
			gain = 350;
			casePlus3 = false;
			break;

		case 14:
			id_case = 14;
			gain = 0;
			casePlus3 = false;
			break;

		case 15:
			id_case = -1;
			gain = 150;
			casePlus3 = false;
			break;

		case 16:
			id_case = -1;
			gain = 200;
			casePlus3 = false;
			break;

		case 17:
			id_case = 8;
			gain = 0;
			casePlus3 = false;
			break;

		case 18:
			id_case = -1;
			gain = 400;
			casePlus3 = false;
			break;

		case 19:
			id_case = 9;
			gain = 0;
			casePlus3 = false;
			break;

		case 20://Carte spéciale
			id_case = -1;
			gain = 0;
			casePlus3 = false;
			break;

		case 21:
			id_case = -1;
			gain = 150;
			casePlus3 = false;
			break;

		case 22:
			id_case = 31;
			gain = 0;
			casePlus3 = false;
			break;

		case 23://Carte spéciale
			id_case = -1;
			gain = 0;
			casePlus3 = false;
			break;

		case 24://Carte spéciale
			id_case = -1;
			gain = 0;
			casePlus3 = false;
			break;
	}
}
