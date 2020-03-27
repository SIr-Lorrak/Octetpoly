#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;


//Constructeur par défaut
Pion::Pion(){
	
	srand(time(NULL));
	karma = rand()%4-2;
	rang = 1;
	bitcoin = INITCOIN;
	nbpropriete = 0;
	pos = 1;
	car = '*';
	prisonnier = 0;
	propriete = new Case*[MAXCASEHT];
}


//-------------------------------------Accesseurs----------------------------------------
string Pion::getNom() const					{ return nom;} 
int Pion::getKarma() const					{ return karma;}
unsigned int Pion::getRang() const			{ return rang;}
float Pion::getCoin() const 				{ return bitcoin;}
unsigned int Pion::getNbPropriete() const 	{ return nbpropriete;}
unsigned int Pion::getPos() const 			{ return pos;}
char Pion::getCar() const 					{ return car;}
bool Pion::getPrisonnier() const 			{ return prisonnier;}


//-------------------------------------Mutateurs-----------------------------------------
void Pion::setCar(const char c){ car = c;}

void Pion::setCoin(const float argent){ bitcoin = argent;}

//-------------------------------------Fonctions et Procédures---------------------------

void Pion::lanceDes()
{
	srand(time(NULL));
	d.D1 = rand()%6+1;
	d.D2 = rand()%6+1;
}

void Pion::avancer()
{
	cout << "Position de départ du pion : " << pos << endl;

	pos = (pos + d.D1 + d.D2)%MAXCASEP;
	
	cout << "Vous avez fait : " << d.D1 << " + " << d.D2 << endl << "Vous avancez donc de " << d.D1 + d.D2 << " cases !" << endl;
}

unsigned int Pion::rapportePlus() const
{
	int n = 0;
	for(unsigned int i = 0; i < nbpropriete ; i++)
	{
		if(propriete[n]->getLoyer()<propriete[i]->getLoyer()) n=i;
	}
	return n;
}

unsigned int Pion::plusCher() const
{
	int n = 0;
	for(unsigned int i = 0; i < nbpropriete ; i++)
	{
		if(propriete[n]->getPrixInitial()<propriete[i]->getPrixInitial()) n=i;
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

void Pion::vendre(){
	//TODO
}

Pion * Pion::getPion(){
  return this;
}

void Pion::acheter(Case * c){
	c->estAcheter(rang); 
	propriete[nbpropriete] = c;
	nbpropriete++;
	unsigned int prix = c->getPrix();
	bitcoin = bitcoin - prix;
}

float Pion::patrimoineActif(){
	float somme = 0;
	for (unsigned int i = 0 ; i < nbpropriete ; i++)
	{
		somme = somme + propriete[i]->getPrixDeVente();
	}
	return somme;
}

//-------------------------------------Destructeur---------------------------------------
Pion::~Pion(){
	//for(unsigned int i=0;i<nbpropriete;i++){
	//	delete propriete[i];
	//}
	delete [] propriete;
}