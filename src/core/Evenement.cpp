#include "Evenement.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <time.h>
#include <stdlib.h>
using namespace std;




//constructeur, permet d'initialiser n
Evenement::Evenement(){

	n = "rien";
	
}


//permet de déclancher un événément lors d'un déplacement en fonction du karma 
void Evenement::Declenchement(){

	if((rand()%99)<10){

		n = "hack";
		tps = 0;
		tempsD = clock();

	}
}


//retourne n (nous de l'évenement en court)
string Evenement::getn(){

	return n;

}


//retourne tps (temps du jours sur l'évenement)
float Evenement::gettps(){

	return tps;

}


//retourne t (bool qui permet de savoir si on gagne ou perd de l'argent )
bool Evenement::getT(){

	return t;

}


//pemet de calculer le temps qu'a mit le joueur a faire l'évenement
void Evenement::fini(){

	tempsF = clock();
	tps = (tempsF-tempsD)/CLOCKS_PER_SEC;

	if (n == "hack"){

		if(tps<=50){ 
			t = true;
		}

		else{
			t = false;
		}
		n = "rien";

	}
}

void Evenement::reset(){

	n = "rien";

}


//-------------------------------------------------------------


//constructeur, initialise le premier, le nb sde saisie et l'affichage
Hacking::Hacking(){

	srand (time(NULL));
	int alea = rand()%8;
	mot = tab_com[alea];
	nbSaisie = 0;
	intAff = 2;

}


//concatene le caractere N au reste du mot
void Hacking::saisir(string N){

		motSaisie = motSaisie + N;

}

void Hacking::effacerLettre()
{
	if(motSaisie.length()>0)
		motSaisie = motSaisie.substr(0, motSaisie.size()-1);
}


//permet de valider ou non le mot saisit par le joueur
void Hacking::valider(){

	if(motSaisie==mot){

		motSuivant();
		intAff = 3;

	}

	else{

		motSaisie = "";
		intAff = 4;

	}
}


//permet de choisr le mot suivant
void Hacking::motSuivant(){

	srand (time(NULL));
	int alea = rand()%8;
	mot = tab_com[alea];
	nbSaisie++;
	motSaisie = "";

}


//retourne le mot actuel
string Hacking::getMot(){

		return mot;

}


//retourne le mot tapé par l'utilisateur
string Hacking::getMotSaisie(){

	return motSaisie;

}


//retourne le nombre de mot validé
unsigned int Hacking::getnbSaisie(){

	return nbSaisie;

}


//retourne un entier qui permet de choisir le bon affichage
int Hacking::getIntAff(){

	return intAff;
	
}


