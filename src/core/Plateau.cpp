#include "Plateau.h"

using namespace std;

Plateau::Plateau(){
	nbcase = 32;
	//tab	= new Case[taille];

	nbJoueur = 0;
	nbOrdi = 0;
	/*
	j1 = new Joueur;
	j2 = new Joueur;
	j3 = new Joueur;
	j4 = new Joueur;
	*/
	/*
	ordi1 =  new Ordi;
	ordi2 =  new Ordi;
	ordi3 =  new Ordi;
	ordi4 =  new Ordi;
	*/

	dimx = 0;
	dimy = 0;
}


Plateau::Plateau(const unsigned int dimensionX, const unsigned int dimensionY, const unsigned int nombreDeJoueur){

	nbcase = 32;
	//tab	= new Case[taille];

	nbJoueur = nbJoueur;
	nbOrdi = 4 - nbJoueur;
	/*
	j1 = new Joueur;
	j2 = new Joueur;
	j3 = new Joueur;
	j4 = new Joueur;

	ordi1 =  new Ordi;
	ordi2 =  new Ordi;
	ordi3 =  new Ordi;
	ordi4 =  new Ordi;
	*/

	dimx = dimensionX;
	dimy = dimensionY;
}


