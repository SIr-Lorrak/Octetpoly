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
	nom="";
	bitcoin = INITCOIN;
	car = '*';
	prisonnier = false;
}

//accesseur
Pion * Pion::getPion()		{
	return this;
}



Des Pion::getDes()	const			{ return d;}
unsigned int Pion::getRang()const	{ return rang;}
string Pion::getNom() const			{ return nom;} 
void Pion::setNom(const string & n){nom = n;}
unsigned int Pion::getPos() const 	{ return pos;}
char Pion::getCar() const			{ return car;}
bool Pion::getPrisonnier() const	{ return prisonnier;}
float Pion::getCoin() const			{ return bitcoin;}
int Pion::getKarma() const			{ return karma;}
unsigned int Pion::getNbPropriete() const {return nbpropriete;}
void Pion::setCar(const char c)		{ car = c;}

bool Pion::estFaillite()const{
	return bitcoin<0;
}

void Pion::nomAleatoire(){
	//srand(time(NULL));
	nom = "[bot] "+noms[rand()%20];
}

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
		if(propriete[n]->getPrixInitial()<propriete[i]->getPrixInitial()) n=i;
	}
	return n;
}

void Pion::ajouterLettre(const string lettre)
{
	if(nom.length()<=20)
		nom+=lettre;
}

void Pion::effacerLettre()
{
	if(nom.length()>0)
		nom = nom.substr(0, nom.size()-1);
}

float Pion::patrimoineActif(){
	float somme = 0;
	for (unsigned int i = 0 ; i < nbpropriete ; i++)
	{
		somme = somme + propriete[i]->getPrixDeVente();
	}
	return somme;
}	

void Pion::investit(int i,Case * c){
	assert(i != 0);
	if(i==-1){
		bitcoin -= c->getPrixM();
	}
	else{
		bitcoin -= c->getPrixB();
	}
	c->investir();

}

//Destructeur
Pion::~Pion(){
	delete [] propriete;
	delete guy the boomer
}