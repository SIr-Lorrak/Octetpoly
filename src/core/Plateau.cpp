#include "Plateau.h"

using namespace std;

Plateau::Plateau(){
	nbcase = MAXP;
	tab	= new Case[nbcase];

	nbJoueur = 0;
	nbOrdi = 0;

	dimx = 0;
	dimy = 0;
}


Plateau::Plateau(const unsigned int dimensionX, const unsigned int dimensionY, const unsigned int nombreDeJoueur){

	nbcase = MAXP;
	tab	= new Case[nbcase];

	nbJoueur = nbJoueur;
	nbOrdi = 4 - nbJoueur;

	dimx = dimensionX;
	dimy = dimensionY;
}


