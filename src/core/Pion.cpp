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
	ticket = false;
	tourUn = false;

}

///---------------------------------------------------------Accesseurs-----------------------------------------------------------

string Pion::getNom() const{
 return nom;
} 

int Pion::getKarma() const{
 return karma;
}

unsigned int Pion::getRang() const{
 return rang;
}

float Pion::getCoin() const{
 return bitcoin;
}

unsigned int Pion::getNbPropriete() const{
 return nbpropriete;
}

unsigned int Pion::getPos() const{
 return pos;
}

char Pion::getCar() const{
 return car;
}

bool Pion::getPrisonnier() const{
 return prisonnier;
}

Pion * Pion::getPion(){
  return this;
}

Des Pion::getDes() const{
	return d;
}

//Permet de savoir si le joueur a un ticket
bool Pion::getTicket() const{
	return ticket;
}

bool Pion::getTourUn() const{
	return tourUn;
}

//Permet de récupérer une propriété du joueur
Case * Pion::getPropriete(unsigned int indice) const{
	return &*propriete[indice];
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

//Permet de modifier la valeur du ticket 
void Pion::setTicket(bool achat){
	ticket = achat;
}


void Pion::setKarma(const unsigned int k){
	karma = k;
}

void Pion::setPrisonnier(){
	if(prisonnier){
		prisonnier = false;
	}
	else{
		prisonnier = true;
	}
}

void Pion::setTourUn(const unsigned int tour){
	tourUn = tour;
}

void Pion::donTicket(){
	ticket = true;
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
		pos +=d.D1 + d.D2;
		//cout << "Le joueur a fait : " << d.D1 << " + " << d.D2 << endl << "Il avance donc de " << d.D1 + d.D2 << " cases !" << endl;

		if(pos >= MAXCASEP)
		{
			salaire();
		}
		pos = pos%MAXCASEP;
		if(pos == 8)
		{
			prisonnier = true;
		}
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
	assert((unsigned int)bitcoin >= c->getPrix());

	bitcoin -= c->getPrix();
	propriete[nbpropriete] = c;
	nbpropriete++;

	c->estAcheter(rang);
}

void Pion::don(Case * c)
{
	propriete[nbpropriete] = c;
	c->setOccupation(rang);
	nbpropriete++;
}

void Pion::vend(string nom)
{
	assert(nbpropriete != 0);

	unsigned int i = 0;
	bool trouver = false;
	while(!trouver && i < nbpropriete)
	{
		if(nom == propriete[i]->getNom())
		{
			bitcoin += propriete[i]->getPrixDeVente();
			propriete[i]->reset();
			propriete[i] = NULL;
			trouver = true;
		}
		i++;
	}

	//Le nom ne correspond pas à une case de propriété
	assert(i<32);

	///Il faut déplacer les propriétés pour qu'il n'y ai pas de case vide entre 2 propriétés
	///On supprime la case vide et on replace les autres propriétés
	for(unsigned int j = i-1; j < nbpropriete - 1 ; j++)
	{
		propriete[j] = propriete[j+1];
	}

	propriete[nbpropriete - 1] = NULL;
	nbpropriete = nbpropriete - 1;
}

void Pion::estRacheter(string nom){
	assert(nbpropriete != 0);

	unsigned int i = 0;
	bool trouver = false;
	while(!trouver && i < nbpropriete)
	{
		if(nom == propriete[i]->getNom())
		{
			propriete[i] = NULL;
			trouver = true;
		}
		i++;
	}

	//Le nom ne correspond pas à une case de propriété
	assert(i<32);

	///Il faut déplacer les propriétés pour qu'il n'y ai pas de case vide entre 2 propriétés
	///On supprime la case vide et on replace les autres propriétés
	for(unsigned int j = i-1; j < nbpropriete - 1 ; j++)
	{
		propriete[j] = propriete[j+1];
	}

	propriete[nbpropriete - 1] = NULL;
	nbpropriete = nbpropriete - 1;
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
        karma = karma - c->getKarmaCase();

        /// Le karma doit être entre -100 et 100
        if(karma < -100)
        {
            karma = -100;
        }
    }
    else{
        bitcoin -= c->getPrixB();
        karma = karma + c->getKarmaCase();

        /// Le karma doit être entre -100 et 100
        if(karma > 100)
        {
            karma = 100;
        }
    }

    c->investir(i);
}

void Pion::EstEnFaillite()
{
	for(unsigned int i = 0; i < nbpropriete; i++)
	{
		propriete[i]->reset();

		propriete[i] = NULL;
	}
	nbpropriete = 0;
	bitcoin = -1;
}


///----------------------------------------------------------------Destructeur--------------------------------------------------------------

Pion::~Pion(){
	delete [] propriete;
}