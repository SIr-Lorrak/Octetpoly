#include "Case.h"
//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	prix = 0;
	loyer = 0;
	prixDeBase = 0;
	prixM = 0;
	prixB = 0;
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

unsigned int Case::getPrixDeBase() const{
	return prixDeBase;
}

int Case::getInvestissement() const{
	return investissement;
}

char Case::getType() const{
	return type;
}
//-------------------------------------Setters-------------------------------------------
void Case::setOccupation(unsigned int occupant){
	occupation = occupant;
}

//-------------------------------------Méthodes------------------------------------------

void Case::initCase(char categorie,unsigned int p){
	prixDeBase = p;
	prix = prixDeBase;
	type = categorie;
}

void Case::initPrixDeBase(){
	prix = prixDeBase;
}

void Case::investir(int i){
	investissement = i;
	//Modifie le prix en conséquence
}
