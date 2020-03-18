#include "Pion.h"

Pion::Pion()
{
	srand(time(NULL));
	karma = rand()%4-2;
	coin = 500;
	nbpropriete = 0;
	propriete = new Case[NBCASE];
	
}

float Pion::getCoin() const
{
	return coin;
}

string Pion::getNom() const
{
	return nom;
} 

void Pion::ajouterLettre(const char lettre)
{
	nom = nom+lettre;
}

unsigned int Pion::getKarma() const
{
	return karma;
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