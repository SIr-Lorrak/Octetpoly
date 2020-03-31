#include "Case.h"
#include <iostream>

using namespace std;

//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	ad = false;
	nom="";

	prix = 0;
	prixInitial = 0;

	loyer = 0;
	loyerInitial = 0;

	prixM = 0;
	prixMInitial = 0;

	prixB = 0;
	prixBInitial = 0;

	prixDeVente = 0;
	prixDeVenteInitial = 0;
}

Case::~Case(){
	//TODO
}

//-------------------------------------Getters-------------------------------------------

string Case::getNom() const{
	return nom;
}

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

void Case::initCase(char categorie,unsigned int p,string n,unsigned int pV,unsigned int pM,unsigned int pB,unsigned int l){
	nom = n;
	type = categorie;

	prixInitial = p;
	prix = prixInitial;
	
	prixDeVenteInitial = pV;
	prixDeVente = prixDeVenteInitial;

	prixMInitial = pM;
	prixM = prixMInitial;

	prixBInitial = pB;
	prixB = prixBInitial;

	loyerInitial = l;
	loyer = loyerInitial;

}


void Case::initPrixInitial(){
	prix = prixInitial;
	prixDeVente = prixDeVenteInitial;
	prixM = prixMInitial;
	prixB = prixBInitial;
	loyer = loyerInitial; 
}


void Case::investir(int i){
	assert(i != 0);
	//Vérifie si l'entreprise n'a pas changé de politique
	if((investissement > 0 && i == -1) || (investissement < 0 && i == 1))
	{
		initPrixInitial();
		investissement = 0;
	}

	if(i == -1)
	{
		investissement--;
		prixM = prixM*1.2;
	}

	else 
	{
		investissement++;
		prixB = prixB*1.3;
	}

	//Investissement > 0 : on opte pour une politique légal
	//Investissement < 0 : on opte pour une politique illégal
	switch(investissement){
		case 1:
			loyer = loyer*1.2;
			prix = prix*1.2;
			prixDeVente = prixDeVente*1.2;
			break;

		case 2:
			loyer = loyer*1.3;
			prix = prix*1.3;
			prixDeVente = prixDeVente*1.3;
			break;

		case 3:
			loyer = loyer*1.4;
			prix = prix*1.4;
			prixDeVente = prixDeVente*1.4;
			break;

		case 4:
			loyer = loyer*1.5;
			prix = prix*1.5;
			prixDeVente = prixDeVente*1.5;
			break;

		case 5:
			loyer = loyer*1.6;
			prix = prix*1.6;
			prixDeVente = prixDeVente*1.6;
			break;

		case -1:
			loyer = loyer*1.2;
			prix = prix*1.2;
			prixDeVente = prixDeVente*1.2;
			break;

		case -2:
			loyer = loyer*1.4;
			prix = prix*1.4;
			prixDeVente = prixDeVente*1.4;
			break;

		case -3:
			loyer = loyer*1.6;
			prix = prix*1.6;
			prixDeVente = prixDeVente*1.6;
			break;

		case -4:
			loyer = loyer*1.8;
			prix = prix*1.8;
			prixDeVente = prixDeVente*1.8;
			break;

		case -5:
			loyer = loyer*2;
			prix = prix*2;
			prixDeVente = prixDeVente*2;
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
	initPrixInitial();
}

//-------------------------------------TEST REGRESSION-----------------------------------

void Case::affichageRegression(){
	cout << endl << "Affichage : ........" << endl;
	cout << "ad : " << ad << endl; 
	cout << "nom : " << nom << endl;
	cout << "occupation : " << occupation << endl;
	cout << "type : " << type << endl; ; 
	cout << "investissement : " << investissement << endl; 

	cout << "loyer : " << loyer << endl; 
	cout << "loyerInitial : " << loyerInitial << endl;

	cout << "prix :" << prix << endl; 
	cout << "prixInitial : " << prixInitial << endl;

	cout << "prixM : " << prixM << endl; 
	cout << "prixMInitial : " << prixMInitial << endl;

	cout << "prixB : " << prixB << endl; 
	cout << "prixBInitial : " << prixBInitial << endl;

	cout << "prixDeVente : " << prixDeVente << endl ;
	cout << "prixDeVenteInitial : " << prixDeVenteInitial << endl;
}

void Case::testRegressionCase(){
	cout << endl << endl;
	cout << "Appel initCase() : ....." << endl;
	initCase('E',35,"testEntreprise",1,7,42,69);
	affichageRegression();

	cout << endl << "Appel estAcheter() : ....." << endl;
	estAcheter(2);
	affichageRegression();

	cout << endl << "Investissement +2" << endl; 
	investir(1);
	investir(1);
	affichageRegression();

	cout << endl << "Investissement -2" << endl;
	investir(-1);
	investir(-1);
	affichageRegression();

	cout << endl << " Appel advertising() :....." << endl;
	advertising(2);
	affichageRegression();

	cout << endl << " Appel endAdvertising() :....." << endl;
	endAdvertising(2);
	affichageRegression();

	cout << endl << " Appel initPrixInitial() :....." << endl;
	initPrixInitial();
	affichageRegression();

	cout << endl << "Appel Reset() :....." << endl;
	reset();
	affichageRegression();


}