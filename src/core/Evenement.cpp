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
bool Evenement::Declenchement(int karma){

	srand (time(NULL));
	unsigned int a;

	if((rand()%100)<25){

		//Accès uniquement au mini-jeu niveau 1 bon
		if(karma >= 0 && karma < 50 )
		{
			a = 2;
		}

		//Accès uniquement au mini-jeu niveau 1 mauvais 
		else if(karma < 0 && karma > -50)
		{
			a = 0;
		}

		//Accès uniquement au mini-jeu niveau 1 mauvais et niveau 2 mauvais
		else if(karma <= -50)
		{
			a = rand()%2;
		}

		//Accès uniquement au mini-jeu niveau 1 bon et niveau 2 bon
		else if(karma >= 50)
		{
			a = (rand()%2)+2;
		}

		if(a ==0){n = "hack";}

		else if(a == 1){n = "escape";}

		else if(a == 2){n = "clicker";}

		else if(a == 3){n = "lucky";}

		tps = 0;
		tempsD = clock();
	}
	n="clicker";
	tps = 0;
	tempsD = clock();
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
			gain = 0;
		}

		else{
			t = false;
			gain = -50;
		}

		
	}

	if (n == "clicker"){

		gain = 0.5*clique;

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
	Fin = false;
}

//permet le gestion du temps et la fin du mini jeu
void Clicker::gestionTps(clock_t tempsD){
	clock_t temps = clock();
	tps_actuel = (temps - tempsD)/CLOCKS_PER_SEC;
	if(tps_actuel > 9){
		Fin = true;
	}
}

//retourne le bool fin
bool Clicker::getFin() const{
	return Fin;
}

//permet d'ajouter un clique au compteur
void Clicker::ajoutClique(){
	if(Fin == false){
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
	Fin = false;
}	


//-----------------------Escape--------------------------------------

Escape::Escape(){
	Joueur.x = 7;
	Joueur.y = 9;
	Police.x = 7;
	Police.y = 10;
	Fin = false;
	echec = false;
	PolicePasse.x=7;
	PolicePasse.y=10;
	P = false;
	//JoueurPasse.x = 7;
	//JoueurPasse.y = 9;

}

void Escape::resetEscape(){
	Joueur.x = 7;
	Joueur.y = 9;
	Police.x = 7;
	Police.y = 10;
	Fin = false;
	echec = false;
	PolicePasse.x=7;
	PolicePasse.y=10;
	P = false;
	JoueurPasse.x = 7;
	JoueurPasse.y = 9;
}

/*bool operator== (const& vec2D a, const& vec2D b){
	return ((a.x==b.x)&&(a.y==b.y));
}*/

void Escape::avancerJoueur(string direction){
	

	if(direction=="z"){

		if((tab_escape[Joueur.y-1][Joueur.x]=="RV")||(tab_escape[Joueur.y-1][Joueur.x]=="T1")||(tab_escape[Joueur.y-1][Joueur.x]=="T2")||(tab_escape[Joueur.y-1][Joueur.x]=="ARRIVE")){
			JoueurPasse.y=Joueur.y;
			JoueurPasse.x=Joueur.x;
			Joueur.y-=1;
		}
		else{
			Joueur.x = JoueurPasse.x;
			Joueur.y = JoueurPasse.y; 

		}
	}
	if(direction=="s"){
		if((tab_escape[Joueur.y+1][Joueur.x]=="RV")||(tab_escape[Joueur.y+1][Joueur.x]=="T3")||(tab_escape[Joueur.y+1][Joueur.x]=="T4")){
			JoueurPasse.y=Joueur.y;
			JoueurPasse.x=Joueur.x;
			Joueur.y+=1;
		}
		else{
			Joueur.x = JoueurPasse.x;
			Joueur.y = JoueurPasse.y; 


		}
	}
	if(direction=="q"){
		if((tab_escape[Joueur.y][Joueur.x-1]=="RH")||(tab_escape[Joueur.y][Joueur.x-1]=="T1")||(tab_escape[Joueur.y][Joueur.x-1]=="T4")){
			JoueurPasse.x=Joueur.x;
			JoueurPasse.y=Joueur.y;
			Joueur.x-=1;
		}
		else{
			Joueur.x = JoueurPasse.x;
			Joueur.y = JoueurPasse.y; 


		}
	}
	if(direction=="d"){
		if((tab_escape[Joueur.y][Joueur.x+1]=="RH")||(tab_escape[Joueur.y][Joueur.x+1]=="T2")||(tab_escape[Joueur.y][Joueur.x+1]=="T3")){
			JoueurPasse.x=Joueur.x;
			JoueurPasse.y=Joueur.y;
			Joueur.x+=1;
		}
		else{
			Joueur.x = JoueurPasse.x;
			Joueur.y = JoueurPasse.y; 


		}
	}
}

//retourne le bool fin
bool Escape::getFin() const{
	return Fin;
}

bool Escape::getEchec(){
	return echec;
}


vec2D Escape::getJoueur(){
	return Joueur;
}

vec2D Escape::getPolice(){
	return Police;
}


void Escape::victoireDefaite(){
	if((Joueur.x==Police.x)&&(Joueur.y==Police.y)){
		Fin = true;
		echec = true;
	}
	else if((Joueur.x==7)&&(Joueur.y==1)){
		
		Fin = true;
	}
}

bool Escape::getFin(){
	return Fin;
}

void Escape::deplacePolice(clock_t tempsD){
	//for(int i=0;i<5;i++){cout<<"aa"<<endl;}
	clock_t temps = clock();
	int tps_actuel = (temps - tempsD)/CLOCKS_PER_SEC;
	if(tps_actuel%2 == 1){P = true;}
	if((tps_actuel%2 == 0)&&(tps_actuel>0)&&(P == true)){
		//for(int i=0;i<5000;i++){cout<<Police.y<<endl;}
		
		if(((tab_escape[Police.y+1][Police.x]=="RV")||(tab_escape[Police.y+1][Police.x]=="T3")||(tab_escape[Police.y+1][Police.x]=="T4"))&&(tab_escape[Police.y+1][Police.x]!=tab_escape[PolicePasse.y][PolicePasse.x])){
			
			PolicePasse.x=Police.x;
			PolicePasse.y=Police.y;
			Police.y+=1;
			P = false;

		}
		else if(((tab_escape[Police.y-1][Police.x]=="RV")||(tab_escape[Police.y-1][Police.x]=="T1")||(tab_escape[Police.y-1][Police.x]=="T2")||(tab_escape[Police.y-1][Police.x]=="DEPART"))&&(tab_escape[Police.y-1][Police.x]!=tab_escape[PolicePasse.y][PolicePasse.x])){
			PolicePasse.x=Police.x;
			PolicePasse.y=Police.y;
			Police.y-=1;
			P = false;
			
		}
		else if(((tab_escape[Police.y][Police.x+1]=="RH")||(tab_escape[Police.y][Police.x+1]=="T2")||(tab_escape[Police.y][Police.x+1]=="T3"))&&(tab_escape[Police.y][Police.x+1]!=tab_escape[PolicePasse.y][PolicePasse.x])){
			PolicePasse.x=Police.x;
			PolicePasse.y=Police.y;
			Police.x+=1;
			P = false;
		}
		else if(((tab_escape[Police.y][Police.x-1]=="RH")||(tab_escape[Police.y][Police.x-1]=="T1")||(tab_escape[Police.y][Police.x-1]=="T4"))&&(tab_escape[Police.y][Police.x-1]!=tab_escape[PolicePasse.y][PolicePasse.x])){
			PolicePasse.x=Police.x;
			PolicePasse.y=Police.y;
			Police.x-=1;
			P = false;
		}
	}
}

//-----------------------------------------LUCKY-------------------------------------------------------
//Constructeur par défaut
Lucky::Lucky(){
	cartePiocher = false;
}

//Destructeur 
Lucky::~Lucky(){

}

//Permet de récupèrer un pointeur sur la carteUn
Carte * Lucky::getCarteUn(){
	return &*carteUn;
}

//Permet de récupèrer un pointeur sur la carteDeux
Carte * Lucky::getCarteDeux(){
	return &*carteDeux;
}

//Permet de connaître la valeur du booléen cartePiocher
bool Lucky::getCartePiocher(){
	return cartePiocher;
}

//Permet de piocher deux cartes 
void Lucky::pioche(){
	carteUn = new Carte;
	carteDeux = new Carte;
	carteUn->randomCarte();
	carteDeux->randomCarte();
	cartePiocher = true;
}

//Reset Lucky
void Lucky::reset(){
	delete carteUn;
	delete carteDeux;
	carteUn = NULL;
	carteDeux = NULL;
	cartePiocher = false;
}


