#include "Jeu.h"

void Plateau::banque(){

}

void Plateau::entreprise(){

}

void Plateau::prison(){
	if (true)
	{
		if(true)//Utilise une carte prison
		{

		}

		else if(true)//Paye pour sortir
		{

		}
		else if(true)//Lancer de dé
		{

		}

		//FIN
	}

	else
	{
		//Le champs prisonier de pion passe à TRUE
		//FIN
	}
}

void Plateau::carteChance(){

}

void Plateau::campagneDePub(){

}

void Plateau::porteOuverte(){

}


//A mettre dans jeu 
void Plateau::ActionCase(){
	switch('A'){
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