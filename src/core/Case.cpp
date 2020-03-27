#include "Case.h"
#include <iostream>

using namespace std;

//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	ad = false;

	prix = 0;
	loyer = 0;
	prixInitial = 0;
	prixM = 0;
	prixB = 0;
	prixDeVente = 0;
}

Case::~Case(){
	//TODO
}

//-------------------------------------Getters-------------------------------------------
unsigned int Case::getOccupation() const{
	return occupation;
}


unsigned int Case::getPrix() const{
	return prix;
}


unsigned int Case::getPrixM() const{
	return prixM;
}


unsigned int Case::getPrixB() const{
	return prixB;
}


unsigned int Case::getLoyer() const{
	return loyer;
}


unsigned int Case::getPrixInitial() const{
	return prixInitial;
}


unsigned int Case::getPrixDeVente() const{
	return prixDeVente;
}


int Case::getInvestissement() const{
	return investissement;
}


char Case::getType() const{
	return type;
}


bool Case::getAd() const{
	return ad;
}


//-------------------------------------Setters-------------------------------------------


//-------------------------------------Méthodes------------------------------------------

void Case::initCase(char categorie,unsigned int p,string nom){
	prixInitial = p;
	prix = prixInitial;
	type = categorie;
	prixDeVente = prixInitial;
	prixM = 1;
	prixB = 1;
	loyer = prixInitial;
}


void Case::initPrixInitial(){
	prix = prixInitial;
}


void Case::investir(int i){
	//Vérifie si l'entreprise n'a pas changé de politique
	//Ici on passe d'une politique tourné dans le légal 
	//Vers une politique orienté dans l'illégale

	if(investissement > 0 && i == -1)
	{
		//On divise les prix par (investissment+1)
		prixDeVente = prixDeVente/(investissement+1);
		prix = prix/(investissement+1);
		loyer = loyer/(investissement+1);
		investissement = -1;
		prixB = 1;
	}

	//Vérifie si l'entreprise n'a pas changé de politique
	//Ici on passe d'une politique tourné dans le illégal 
	//Vers une politique orienté dansle légale
	else if(investissement < 0 && i == 1)
	{
		//On divise les prix par (investissment*2)
		prixDeVente = prixDeVente/(investissement*2);
		prix = prix/(investissement*2);
		loyer = loyer/(investissement*2);
		investissement = 1;
		prixM = 1;
	}

	else if(i == -1)
	{
		investissement--;
		prixM = prixM*2;
	}

	else if(i == 1)
	{
		investissement++;
		prixB = prixB*2;
	}

	//Investissement > 0 : on opte pour une politique légal
	//Investissement < 0 : on opte pour une politique illégal
	switch(investissement){
		case 1:
			loyer = loyer*2;
			prix = prix*2;
			prixDeVente = prixDeVente*2;
			break;

		case 2:
			loyer = loyer*3;
			prix = prix*3;
			prixDeVente = prixDeVente*3;
			break;

		case 3:
			loyer = loyer*4;
			prix = prix*4;
			prixDeVente = prixDeVente*4;
			break;

		case 4:
			loyer = loyer*5;
			prix = prix*5;
			prixDeVente = prixDeVente*5;
			break;

		case 5:
			loyer = loyer*6;
			prix = prix*6;
			prixDeVente = prixDeVente*6;
			break;

		case -1:
			loyer = loyer*2;
			prix = prix*2;
			prixDeVente = prixDeVente*2;
			break;

		case -2:
			loyer = loyer*4;
			prix = prix*4;
			prixDeVente = prixDeVente*4;
			break;

		case -3:
			loyer = loyer*6;
			prix = prix*6;
			prixDeVente = prixDeVente*6;
			break;

		case -4:
			loyer = loyer*8;
			prix = prix*8;
			prixDeVente = prixDeVente*8;
			break;

		case -5:
			loyer = loyer*10;
			prix = prix*10;
			prixDeVente = prixDeVente*10;
			break;
	}
}

void Case::estAcheter(unsigned int i){
	occupation = i;
	prix = prix*2;
}

void Case::advertising(unsigned int i){
	ad = true;
	prix = prix*i;
	loyer = loyer*i;
	prixDeVente = prixDeVente*i;
}

void Case::endAdvertising(unsigned int i){
	ad = false;
	prix = prix/i;
	loyer = loyer/i;
	prixDeVente = prixDeVente/i;
}

void Case::reset(){
	occupation = 0;
	investissement = 0;
	ad = false;

	//On renitialise les prix
	prix = prixInitial;
	loyer = prixInitial;
	prixDeVente = prixInitial;
	prixM = 1;
	prixB = 1;

}