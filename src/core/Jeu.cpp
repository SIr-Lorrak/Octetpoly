#include "Jeu.h"

//-------------------------------------Constructeurs--------------------------------------

Jeu::Jeu(){
	board;
}

Jeu::Jeu(unsigned int nbO){
	board;
	nbOrdi = nbO;
	tabO[nbOrdi];
}

Jeu::~Jeu(){
	//TODO
}

//-------------------------------------Méthodes------------------------------------------
void Jeu::banque(){
	if(tourOrdi)
	{
		unsigned int posO = tabO[joueurCourant-1].getPos();
		if(true)
		{

		}

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
	//TODO enlever num pour le remplacer par tabJ[joueurCourant-1];
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