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
	tempsF=0;
	
}


//permet de déclancher un événément lors d'un déplacement en fonction du karma 
bool Evenement::Declenchement(){

	srand (time(NULL));

	if((rand()%100)<5){

		if((rand()%2)==0){n = "hack";}

		else{n = "hack";}

		tps = 0;
		tempsD = clock();

	}
	return n != "rien";
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
void Evenement::fini(int clique){

	tempsF = clock();
	tps = (tempsF-tempsD)/CLOCKS_PER_SEC;

	if (n == "hack"){

		if(tps<=50){ 
			t = true;
		}

		else{
			t = false;
			gain = -50;
		}

		
	}

	if (n == "clicker"){

		gain = 3*clique;

	}
}

void Evenement::reset(){
	n = "rien";
	tempsF=0;
}

//retourne le gain à la fin de l'évenement
int Evenement::getgain(){

	return gain;

}


//retourne le temps de départ
clock_t Evenement::gettempsD(){

	return tempsD;

}

clock_t Evenement::getTempsF() const{
	return tempsF;
}


//-------------------------------------------------------------


//constructeur, initialise le premier, le nb sde saisie et l'affichage
Hacking::Hacking(){

	srand (time(NULL));
	int alea = rand()%8;
	mot = tab_com[alea];
	nbSaisie = 0;
	intAff = 2;
	fin = false;
	nbMot = 4;

}


//concate le caractere N au reste du mot
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
	if(nbSaisie>=nbMot){
		fin = true;
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

unsigned int Hacking::getnbMot(){
	return nbMot;
}


//retourne un entier qui permet de choisir le bon affichage
int Hacking::getIntAff(){

	return intAff;
	
}

bool Hacking::getFin() const{
	return fin;
}

//permet de reset les données membres à la fin de l'évenement hacking
void Hacking::resetHack(){
	srand (time(NULL));
	int alea = rand()%8;
	mot = tab_com[alea];
	motSaisie="";
	nbSaisie = 0;
	intAff = 2;
	fin = false;
}


//-----------------------------------------------------------------------------


//constructeur met le nombre de clique et le temps à 0
Clicker::Clicker(){
	nbclique = 0;
	tps_actuel = 0;
}


//permet d'ajouter un clique au compteur
void Clicker::ajoutClique(clock_t tempsD){
	clock_t temps = clock();
	tps_actuel = (temps - tempsD)/CLOCKS_PER_SEC;
	if(tps_actuel < 10){
		nbclique++;
	}

}


//retourne le temps actuel pour le timer
float Clicker::gettps_actuel(){
	return tps_actuel;
}


//retourne le nombre d'appuie 
unsigned int Clicker::getnbclique(){
	return nbclique;
}


//permet de reset les données membres à la fin de l'évenement Clicker
void Clicker::resetClicker(){

	nbclique = 0;
	tps_actuel = 0;
}

