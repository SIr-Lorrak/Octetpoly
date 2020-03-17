#include "Case.h"
//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	prix = 0;
	prixDeBase = 0;
}

Case::~Case(){
	//TODO
}

//-------------------------------------Getters-------------------------------------------
unsigned int Case::getOccupation(){
	return occupation;
}

char Case::getType(){
	return type;
}

int Case::getInvestissement(){
	return investissement;
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
