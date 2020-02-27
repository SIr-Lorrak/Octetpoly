#include "Pion.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//Constructeur par défaut
Pion::Pion(){

	x = 0;
	karma = 0;
	bitcoin = INITCOIN;
	for (int i = 0; i < MAXCASEHT; i++)
		{
			IndCaseAchetee[i] = -1;
		}
	c = '*';

}

Pion::Pion(){


}

//Accesseurs
int Pion::getpos()const{ return pos;}
int Pion::getkarma()const{ return karma;}
float Pion::getbitcoin()const{ return bitcoin;}
int Pion::getIndCaseAchetee(){

//A faire

}

//Mutateurs
void Pion::setpos(const float pos1){ pos = pos1;}
void Pion::setkarma(){ /*A faire*/ }

//Fonction
int Avancer(int pos)
{
	srand (time(NULL));      		//Initialisation de la fonction rand
	int d1 = rand() % 6 + 1; 		//entier aléatoire entre 1 et 6 
	int d2 = rand() % 6 + 1;
	pos = pos + d1 + d2;
	if(pos > MAXCASEP)
	{
		pos = pos - MAXCASEP - 1
	}
	
	return pos;
}

//Destructeur