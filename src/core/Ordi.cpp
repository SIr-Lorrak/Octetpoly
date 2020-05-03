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


bool Ordi::AIacheteBanque(const Case * banque) const
{
	assert(banque->getOccupation() != getRang());
	return (getCoin()>(1+(0.5-risque/200.0))*banque->getPrix());
}


bool Ordi::AIacheteEntreprise(const Case * entreprise) const
{
	assert(entreprise->getOccupation() != getRang());
	return ((getCoin()>(1.1+(0.5-risque/200.0))*entreprise->getPrix())&&getNbPropriete()>=4)||((getCoin()>(int)entreprise->getPrix())&&getNbPropriete()<4);
}


unsigned int Ordi::AIchampionat() const
{
	if(risque>50) return rapportePlus();//organise les championnats sur la case rapportant le plus actuellement
	else return plusCher();//organise les championnats sur la case ayant le coût d'achat le plus cher
}


int Ordi::AIinvesti(const Case * entreprise) const
{
	assert(entreprise->getOccupation() == getRang());
	int limite;
	if(getTourUn()){
		limite = 16;
	}
	else{
		limite = 4;
	}
	if(entreprise->getInvestissement() == 0){
		if(getKarma()>risque-50){
			if((int)entreprise->getPrixM()<getCoin()) return -1;
		}
		else{
			if((int)entreprise->getPrixB()<getCoin()) return 1;
		}
	}
	else if(entreprise->getInvestissement()*entreprise->getInvestissement()<=limite){
		if(entreprise->getInvestissement()<0){
			if((int)entreprise->getPrixM()<getCoin()) return -1;
		}
		else{
			if((int)entreprise->getPrixB()<getCoin()) return 1;
		}
	}
	return 0;
}

bool estPasDans(const string & nom,const string tabDeNom[],const unsigned int n){
	for(unsigned int i=0;i<n;i++){
		if(nom==tabDeNom[i]){
			return false;
		}
	}
	return true;
}

string Ordi::AIvend(const string dejaVendu[],unsigned int nbVente)const{
	Case * meilleurTaux = NULL;
	for(unsigned int i=0;i<getNbPropriete();i++){
		if(estPasDans(getPropriete(i)->getNom(),dejaVendu,nbVente)){
			Case * c = getPropriete(i);
			if(meilleurTaux == NULL){
				meilleurTaux = c;
			}
			else if((c->getPrixDeVente()/c->getLoyer())>(meilleurTaux->getPrixDeVente()/meilleurTaux->getLoyer())){
				meilleurTaux = c;
			}
		}
	}
	return meilleurTaux->getNom();
}