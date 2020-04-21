#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <assert.h>

using namespace std;


///-----------------------------------------------------Constructeur par défaut------------------------------------------------------

Pion::Pion(){
	
	srand(time(NULL));

	karma = rand()%4-2;
	rang = 0;
	nom="";
	bitcoin = INITCOIN; 
	nbpropriete = 0;
	pos = 0;
	car = '*';
	prisonnier = false;
	propriete = new Case*[MAXCASEHT];

	for(int i = 0; i < 3; i++)
	{
		doubles[i] = false;
	}

}

///---------------------------------------------------------Accesseurs-----------------------------------------------------------

string Pion::getNom() const					
{ return nom;} 

int Pion::getKarma() const					
{ return karma;}

unsigned int Pion::getRang() const			
{ return rang;}

float Pion::getCoin() const 				
{ return bitcoin;}

unsigned int Pion::getNbPropriete() const 	
{ return nbpropriete;}

unsigned int Pion::getPos() const 			
{ return pos;}

char Pion::getCar() const 					
{ return car;}

bool Pion::getPrisonnier() const 			
{ return prisonnier;}

Pion * Pion::getPion(){
  return this;
}

Des Pion::getDes() const{
	return d;
}


///-------------------------------------------------------------------Mutateurs---------------------------------------------------------------
void Pion::setCar(const char c){
	car = c;
}

void Pion::setNom(const string & n){
	nom = n;
}

void Pion::setCoin(const float argent){
	bitcoin = argent;
}

void Pion::setRang(const unsigned int r){
	rang = r;
}

void Pion::setPos(const unsigned int p){
	pos = p;
}

///-------------------------------------------------------------Fonctions et Procédures-------------------------------------------------------


void Pion::nomAleatoire(){
	//srand(time(NULL));
	nom = "[bot] "+noms[rand()%20];
}

void Pion::lanceDes()
{
	//cout << "Le joueur lance les dés !" << endl;
	d.D1 = rand()%6+1;
	d.D2 = rand()%6+1;

	if(d.D1 == d.D2)
	{
		unsigned int i = 0;
		if(prisonnier == true){
			prisonnier = false;
		}

		while(doubles[i] == true)
		{
			i++;
		}

		if(i == 2)
		{
			prisonnier = true;
			pos = 8;
		}
		doubles[i] = true;
	}

	else
	{
		for(unsigned int i = 0; i < 3; i++)
		{
			doubles[i]=false;
		}
			
	}
}

void Pion::avancer()
{
	if(prisonnier == false)
	{
		pos += d.D1 + d.D2;
		//cout << "Le joueur a fait : " << d.D1 << " + " << d.D2 << endl << "Il avance donc de " << d.D1 + d.D2 << " cases !" << endl;

		if(pos > MAXCASEP)
		{
			pos = pos%32;
		}

		if(pos == 8)
		{
			prisonnier = true;
		}

		salaire();
	}
	
}


void Pion::salaire()
{
	float argentCD = 20;
	if(pos < d.D1 + d.D2)
	{
		//cout << "Le joueur est sur la case départ, il reçoit donc 20 bitcoins !" << endl;
		bitcoin += argentCD;
		//cout << "Le joueur a un total de " << bitcoin << "bitcoins." << endl;
	}
}


void Pion::achete(Case * c)
{
	assert(bitcoin > c->getPrix());

	bitcoin -= c->getPrix();
	propriete[nbpropriete] = c;
	nbpropriete++;

	c->estAcheter(rang);
}

void Pion::vend(unsigned int indP, Case * c)
{
	assert(nbpropriete != 0);
	assert(indP < nbpropriete);

	bitcoin += c->getPrixDeVente();
	propriete[indP] = NULL;
	
	///Il faut déplacer les propriétés pour qu'il n'y ai pas de case vide entre 2 propriétés

	///On supprime la case vide et on replace les autres propriétés
	for(unsigned int j = indP; j < nbpropriete; j++)
	{
		propriete[j] = propriete[j+1];
	}

	propriete[nbpropriete] = NULL;
	nbpropriete -= 1;

	c->reset();
}


unsigned int Pion::patrimoineActif(){
	unsigned int somme = 0;
	for (unsigned int i = 0 ; i < nbpropriete ; i++)
	{
		somme = somme + propriete[i]->getPrixDeVente();
	}
	return somme;
}	

unsigned int Pion::rapportePlus() const
{
	int n = 0;
	for(unsigned int i = 0; i < nbpropriete ; i++)
	{
		if(propriete[n]->getLoyer() < propriete[i]->getLoyer()) n=i;
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
    if(nom.length()<=20)
        nom+=lettre;
}


void Pion::effacerLettre()
{
    if(nom.length()>0)
        nom = nom.substr(0, nom.size()-1);
}

void Pion::investit(int i,Case * c){
	assert(i != 0);
	if(i==-1){
		bitcoin -= c->getPrixM();
	}
	else{
		bitcoin -= c->getPrixB();
	}
	c->investir(i);
}


///----------------------------------------------------------------Destructeur--------------------------------------------------------------

Pion::~Pion(){
	delete [] propriete;
}