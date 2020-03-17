#include "Jeu.h"

//-------------------------------------Constructeurs--------------------------------------

Jeu::Jeu(){
	board;
}

Jeu::Jeu(unsigned int nbO){
	board;
	nbOrdi = nbO;
}

Jeu::~Jeu(){
	//TODO
}

//-------------------------------------Méthodes------------------------------------------
void Jeu::banque(){
	if(tourOrdi)
	{

	}
	else
	{

	}

}

void Jeu::entreprise(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}

void Jeu::prison(){
	if(tourOrdi){
		

	}
	else{
		
	}
}

void Jeu::carteChance(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}

void Jeu::campagneDePub(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}

void Jeu::porteOuverte(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}


//A mettre dans jeu 
void Jeu::actionCase(unsigned int num){

	Case & c = board.getCase(num);
	switch(c.getType()){
		case 'E':
			entreprise();
			break;

		case 'B':
			banque();
			break;

		case 'C':
			carteChance();
			break;

		case 'A':
			campagneDePub();
			break;

		case 'O':
			porteOuverte();
			break;

		case 'I':
			//TODO
			break;

		case 'D':
			//TODO
			break;

		case 'P':
			prison();
			break;
	}
}

void Jeu::tourSuivant(){

}