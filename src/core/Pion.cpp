#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <assert.h>

using namespace std;


//Constructeur par défaut
Pion::Pion(){
	
	srand(time(NULL));

	karma = rand()%4-2;
	rang = 0;
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


//Accesseurs
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


//Mutateurs
void Pion::setCar(const char c){ car = c;}

void Pion::setCoin(const float argent){ bitcoin = argent;}

//Fonctions et Procédures

void Pion::lanceDes()
{
	cout << "Le joueur lance les dés !" << endl;
	srand(time(NULL));
	d.D1 = rand()%6+1;
	d.D2 = rand()%6+1;

	if(d.D1 == d.D2)
	{
		unsigned int i = 0;

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

void Pion::avance()
{
	if(prisonnier == false)
	{
		pos += d.D1 + d.D2;
		cout << "Le joueur a fait : " << d.D1 << " + " << d.D2 << endl << "Il avance donc de " << d.D1 + d.D2 << " cases !" << endl;

		if(pos > MAXCASEP)
		{
			pos = pos - MAXCASEP - 1;
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
		cout << "Le joueur est sur la case départ, il reçoit donc 20 bitcoins !" << endl;
		bitcoin += argentCD;
		cout << "Le joueur a un total de " << bitcoin << "bitcoins." << endl;
	}
}

void Pion::vendrePropriete()
{
	cout << "Voici les villes possédées par le joueur, " << endl;
	for(unsigned int i = 0; i < nbpropriete; i++)
	{
		//cout << propriete[i].
	}
}

void Pion::achete(Case * c)
{
	assert(bitcoin > c->getPrix());
	bitcoin -= c->getPrix();
	propriete[nbpropriete] = c;
	nbpropriete++;

	//c->estAcheter(rang);
}

/*

void Pion::prison()
{
	if(prisonnier == true)
	{
		int choix;
		cout << "Le joueur est en prison, voici les possibilitées qui s'offrent à lui pour sortir :" << endl
			 <<	"1 : Dépenser 20 bitcoins" << endl
			 << "2 : Lancer les dés afin de faire un double" << endl;
			 
		if(Le le joueur a une carte sortir de prison)
		cout << "3 : Utiliser sa carte "Sortir de Prison"" << endl;
		 
		cout << "Faites votre choix en tapant 1 ou 2" << endl;
		cin >> choix;
		
		switch(choix)

		case 1 :	cout << "Le joueur a choisi de payer 20 bitcoins pour sortir !" << endl;
					bitcoin -= 20;
					cout << "L'argent du joueur est désormais de " << bitcoin << " bitcoins." << endl;
					break;

		case 2 :	cout << "Le joueur a choisi de tenter sa chance aux dés pour sortir !"
					lanceDes();

					if(d.D1 == d.D2)
						{
							cout << "Le joueur à fait un double. Il sort donc de prison !" << endl;
							prisonnier = false;
							avance();
						}

					else
						{ 
							cout << "Le joueur a fait : " << d.D1 << " + " << d.D2 << endl; 
							cout << "Le joueur n'a pas fait de double ! Il reste donc en prison !" << endl;
						}	

					break;


		case 3 :


		break;

		default:
		cout << "OMG ERREUR";
		break;
	}
	else
	{

	}
}*/
/*
void Pion::prisonLancerD()
{
	if(prisonnier == true)
	{
		cout << "Le joueur est en prison," << endl;
		cout << "Il choisit de lancer les dés afin de faire un double pour sortir !" << endl;
		lanceDes();

		if(d.D1 == d.D2)
				{
					cout << "Le joueur à fait un double ! Il sort donc de prison !" << endl;
					prisonnier = false;
					avancer();
				}

		else{ 
			cout << "Le joueur a fait : " << d.D1 << " + " << d.D2 << endl; 
			cout << "Le joueur n'a pas fait de double ! Il reste donc en prison !" << endl;}	
	}
}*/
/*
void Pion::liberteToPrison()
{

}*/

unsigned int Pion::rapportePlus() const
{
	int n = 0;
	for(unsigned int i = 0; i < nbpropriete ; i++)
	{
		if(propriete[n]->getRapport()<propriete[i]->getRapport()) n=i;
	}
	return n;
}

unsigned int Pion::plusCher() const
{
	int n = 0;
	for(unsigned int i = 0; i < nbpropriete ; i++)
	{
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

float Pion::ReventeToFaillite()
{
	float res = 0;
	for(unsigned int i = 0; i < nbpropriete; i++)
	{
		res += propriete[i]->getPrix();
	}
	
	return res;
}

//Destructeur
Pion::~Pion(){
	for(unsigned int i=0;i<nbpropriete;i++){
		delete propriete[i];
	}
	delete [] propriete;
}


/*

				cout << "Le joueur 1 relance les dés !" << endl;
				lanceDes();

				if(d.D1 == d.D2)
				{
					cout << "Le joueur 1 a fait un double !"
					pos = (pos + d.D1 + d.D2)%MAXCASEP;
					cout << "Vous avez fait : " << d.D1 << " + " << d.D2 << endl << "Vous avancez donc de " << d.D1 + d.D2 << " cases !" << endl;

					cout << "Attention ! Si le joueur 1 fait 3 lancés de double à la suite, il va en prison ! " << endl;
					cout << "Le joueur 1 relance les dés !" << endl;
					lanceDes();
					if(d.D1 == d.D2)
					{
						cout << "Malchance ! Le joueur 1 a fait 3 doubles à la suite ! Il va donc en prison !"
						prisonnier = true;
					}
				}
				else
				{
					pos = (pos + d.D1 + d.D2)%MAXCASEP;
					cout << "Vous avez fait : " << d.D1 << " + " << d.D2 << endl << "Vous avancez donc de " << d.D1 + d.D2 << " cases !" << endl;
				}
			}
			*/