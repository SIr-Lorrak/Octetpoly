#include "Case.h"
#include <iostream>

using namespace std;

//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	groupe = 0;
	karmaCase = 0;

	ad = false;
	coeffAd = 1.0;
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

void Case::set(unsigned int p,unsigned int l,unsigned int prixdevente,unsigned int pM,unsigned int pB,unsigned int prop, int i){
	prix = p;
	loyer = l;
	prixDeVente = prixdevente;
	prixM = pM;
	prixB = pB;
	occupation = prop;
	investissement = i;
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

unsigned int Case::getGroup() const{
	return groupe;
}

unsigned int Case::getKarmaCase() const{
	return karmaCase;
}

//-------------------------------------Setters-------------------------------------------

void Case::setOccupation(unsigned int r){
	occupation = r;
}

//-------------------------------------Méthodes------------------------------------------

// Permet l'initialisation d'une case au lancement d'une partie 
//(prix de base,type,nom de la case,etc)
void Case::initCase(unsigned int group,char categorie,unsigned int p,
					string n,unsigned karma,unsigned int pV,
					unsigned int pM,unsigned int pB,unsigned int l){
	nom = n;
	type = categorie;
	groupe = group;
	karmaCase = karma;

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

//Initialise les prix initiaux d'une entreprise ou d'une banque
void Case::initPrixInitial(){
	//Utile pour la fonction investissement car quand on investit, c'est qu'on posséde
	//la case ainsi le loyer initial est égal au prixInitial*2 après achat
	if(occupation > 0)
	{
		prix = 2*prixInitial;
	}

	//Utile pour la fonction reset, on remet bien tout au prix initial vu que la 
	//case n'appartient plus à personne
	else
	{
		prix = prixInitial;
	}

	prixDeVente = prixDeVenteInitial;
	prixM = prixMInitial;
	prixB = prixBInitial;
	loyer = loyerInitial; 
}

//Change l'investissment, le prix,le loyer,le prix de vente,le prixB, le prixM
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

void Case::advertising(){
	ad = true;
	coeffAd = coeffAd*1.2;
	prix = prix*coeffAd;
	loyer = loyer*coeffAd;
	prixDeVente = prixDeVente*coeffAd;
}

void Case::endAdvertising(){
	ad = false;
	prix = prix/coeffAd;
	loyer = loyer/coeffAd;
	prixDeVente = prixDeVente/coeffAd;
	coeffAd = 1.0;
}

void Case::reset(){
	occupation = 0;
	investissement = 0;
	ad = false;
	coeffAd = 1.0;

	//On renitialise les prix
	initPrixInitial();
}

//-------------------------------------TEST REGRESSION-----------------------------------

void Case::affichageRegression(){
	cout << endl << "Affichage : ........" << endl;
	cout << "ad : " << ad << endl; 
	cout << "coeffAd : " << coeffAd << endl; 
	cout << "nom : " << nom << endl;
	cout << "occupation : " << occupation << endl;
	cout << "type : " << type << endl; ; 
	cout << "investissement : " << investissement << endl; 
	cout << "groupe : " << groupe << endl;
	cout << "karma : " << karmaCase << endl;

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
	initCase(1,'E',35,"testEntreprise",10,45,7,42,69);
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
	advertising();
	affichageRegression();

	cout << endl << " Appel endAdvertising() :....." << endl;
	endAdvertising();
	affichageRegression();

	cout << endl << " Appel initPrixInitial() :....." << endl;
	initPrixInitial();
	affichageRegression();

	cout << endl << "Appel Reset() :....." << endl;
	reset();
	affichageRegression();
}