#include "Case.h"
//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	prix = 0;
	loyer = 0;
	prixInitial = 0;
	prixM = 0;
	prixB = 0;
	prixDeVente = 0;
	ad = false;
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
	return prix;
}

unsigned int Case::getPrixB() const{
	return prix;
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

void Case::initCase(char categorie,unsigned int p){
	prixInitial = p;
	prix = prixInitial;
	type = categorie;
}

void Case::initPrixInitial(){
	prix = prixInitial;
}

void Case::investir(int i){
	investissement = i;
	//Modifie le prix en conséquence
}

void Case::estAcheter(unsigned int i){
	occupation = i;
	//TODO modifier les prix
}

void Case::advertising(unsigned int i){
	ad = true;
	prix = prix*i;
	prixDeVente = prixDeVente*i;
	prixInitial = prixInitial*i;
}

void Case::endAdvertising(unsigned int i){
	ad = false;
	prix = prix/i;
	prixDeVente = prixDeVente/i;
	prixInitial = prixInitial/i;
}