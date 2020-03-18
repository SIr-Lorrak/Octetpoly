#include "Pion.h"

Pion::Pion()
{
	pos = 0;
	srand(time(NULL));
	karma = rand()%101;
	coin = 500;
	nbpropriete = 0;
	
}

unsigned int Pion::getPos() const
{
	return pos;
}

float Pion::getCoin() const
{
	return coin;
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
		
unsigned int Pion::rapportePlus() const
{
	return 0;
}
unsigned int Pion::plusCher() const
{
	return 0;
}