#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Pion::Pion()
{
	srand(time(NULL));
	karma = rand()%4-2;
	nbpropriete = 0;
	rang = 0;
	propriete = new Case*[MAXCASEHT];
	pos = 0;
	bitcoin = INITCOIN;
	car = '*';
	prisonnier = false;
}

//accesseur
unsigned int Pion::getRang()const	{ return rang;}
string Pion::getNom() const			{ return nom;} 
unsigned int Pion::getPos() const 	{ return pos;}
char Pion::getCar() const			{ return car;}
bool Pion::getPrisonnier() const	{ return prisonnier;}
float Pion::getCoin() const			{ return bitcoin;}
int Pion::getKarma() const			{ return karma;}
unsigned int Pion::getNbPropriete() const {return nbpropriete;}
void Pion::setCar(const char c)		{ car = c;}

void Pion::lanceDes()
{
	srand(time(NULL));
	d.D1 = rand()%6+1;
	d.D2 = rand()%6+1;
}

void Pion::avancer()
{
	pos = (pos + d.D1 + d.D2)%MAXCASEP;
}
		
unsigned int Pion::rapportePlus() const
{
	int n = 0;
	for(unsigned int i = 0; i<nbpropriete ; i++){
		if(propriete[n]->getLoyer()<propriete[i]->getLoyer()) n=i;
	}
	return n;
}

unsigned int Pion::plusCher() const
{
	int n = 0;
	for(unsigned int i = 0; i<nbpropriete ; i++){
		if(propriete[n]->getPrixDeBase()<propriete[i]->getPrixDeBase()) n=i;
	}
	return n;
}

void Pion::ajouterLettre(const string lettre)
{
	if(nom.length()>=20)
		nom+=lettre;
}

void Pion::effacerLettre()
{
	if(nom.length()>0)
		nom = nom.substr(0, nom.size()-1);
}

//Destructeur
Pion::~Pion(){
	for(unsigned int i=0;i<nbpropriete;i++){
		delete propriete[i];
	}
	delete [] propriete;
}