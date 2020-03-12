#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Case.h"

//Constructeur par défaut
Pion::Pion(){
	pos = 0;
	karma = 0;
	bitcoin = INITCOIN;
	for (int i = 0; i < MAXCASEHT; i++)
		{
			proprietes[i] = 0;
		}
	c = '*';
	prisonnier = false;

}


//Accesseurs
int Pion::getpos(){ return pos;}
int Pion::getkarma(){ return karma;}
float Pion::getbitcoin(){ return bitcoin;}
//int Pion::getIndCaseAchetee(){} //TODO
char Pion::getc(){ return c;}
bool Pion::getprisonnier(){ return prisonnier;}


//Mutateurs
void Pion::setc(const char c1){ c = c1;}

//Fonction
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

void Pion::Prison()
{

	nom = Case::getnom();
	pos = Case::getindCase();

	if(prisonnier == false && nom == "Prison")
	{
		prisonnier = true;
	}

	if(prisonnier == false && pos = "indice de la case prison : 8 ?")
	{
		prisonnier = true;
	}

}


//Destructeur

Pion::~Pion(){}