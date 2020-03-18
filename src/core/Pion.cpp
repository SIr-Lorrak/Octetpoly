#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Pion::Pion()
{
	srand(time(NULL));
	karma = rand()%4-2;
	nbpropriete = 0;
	propriete = new Case[NBCASE];
	pos = 0;
	bitcoin = INITCOIN;
	c = '*';
	prisonnier = false;
}

string Pion::getNom() const
{
	return nom;
} 

int Pion::getpos(){ return pos;}
char Pion::getc(){ return c;}
bool Pion::getprisonnier(){ return prisonnier;}
float Pion::getbitcoin(){ return bitcoin;}
unsigned int Pion::getKarma() const
{
	return karma;
}
void Pion::setc(const char c1){ c = c1;}
void Pion::Avancer(int pos, Des des)
{
	srand (time(NULL));      		//Initialisation de la fonction rand

	des.D1 = rand() % 6 + 1;		//entier aléatoire entre 1 et 6 
	des.D1 = rand() % 6 + 1;


	pos = pos + des.D1 + des.D2;
	if(pos > MAXCASEP)
	{
		pos = pos - MAXCASEP - 1;
	}

}

unsigned int Pion::getNbPropriete() const
{
	return nbpropriete;
}
unsigned int Pion::getRang() const
{
	return rang;
}
		
Case & Pion::rapportePlus() const
{
	return propriete[0];
}
Case & Pion::plusCher() const
{
	return propriete[0];
}


//Destructeur
Pion::~Pion(){}