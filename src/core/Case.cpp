#include "Case.h"
//---------------------------------Constructeur------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
}

Case::~Case(){
	//TODO
}

//-------------------------------------Getters-------------------------------------------
int Case::getoccupation(){
	return occupation;
}

char Case::gettype(){
	return type;
}

int Case::getinvestissement(){
	return investissement;
}

//-------------------------------------Setters-------------------------------------------
void Case::setoccupation(int occupant){
	occupation = occupant;
}

void Case::settype(char categorie){
	type = categorie;
}

void Case::setinvestissement(int i){
	investissement = i;
}