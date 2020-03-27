#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Ordi.h"

const int CASECHAMPIONAT = 12;

Ordi::Ordi()
{
	srand(time(NULL));
	risque = rand() % 101;
	unsigned int alea = rand()%20;
	setNom("[bot] "+noms[alea]);
}

Ordi::Ordi(const unsigned int r)
{
	assert(r<=100);
	risque = r;
}

bool Ordi::AIacheteBanque(const Case & banque) const
{
	assert(banque.getOccupation() != getRang());
	return (getCoin()>(1+(0.5-risque/200.0))*banque.getPrix());
}


bool Ordi::AIacheteEntreprise(const Case & entreprise) const
{
	assert(entreprise.getOccupation() != getRang());
	return ((getCoin()>(1.1+(0.5-risque/200.0))*entreprise.getPrix())&&getNbPropriete()>=4)||((getCoin()>entreprise.getPrix())&&getNbPropriete()<4);
}

unsigned int Ordi::AIchampionat() const
{
	if(risque>50) return rapportePlus();//organise les championats sur la case rapportant le plus actuellement
	else return plusCher();//organise les championats sur la case ayant le coût d'achat le plus cher
}

int Ordi::AIinvesti(const Case & entreprise) const
{
	assert(entreprise.getOccupation() == getRang());
	int i = 0;
	int dernierchoix = 0;
	do{
		if(entreprise.getInvestissement() == 0){
			if(getKarma()>int(50-risque/2)){
				if(entreprise.getPrixM()<getCoin()) dernierchoix = -1;
			}
			else{
				if(entreprise.getPrixB()<getCoin()) dernierchoix = 1;
			}
		}
		else if(entreprise.getInvestissement()*entreprise.getInvestissement()<16){
			if(entreprise.getInvestissement()<0){
				if(entreprise.getPrixM()<getCoin()) dernierchoix = -1;
			}
			else{
				if(entreprise.getPrixB()<getCoin()) dernierchoix = 1;
			}
		}
		else{
			dernierchoix = 0;
		}
		dernierchoix = 0;
		i+=dernierchoix;
	}while(dernierchoix!=0);
	return i;
}