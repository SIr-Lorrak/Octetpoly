#include <iostream>
#include <string>
using namespace std;

#include "Jeu.h"


//seteur permetant de mettre à jour l'évenement e
void Jeu::sete(unsigned int n){

	switch(n){

		case 1:
			e.Declenchement();
			break;

		case 2:
			e.fini();
			break;

	}
}


//seteur permetant de mettre à jour hacking h
void Jeu::seth(unsigned int n){

	switch(n){

		case 1:
			h.intAff = 0;
			break;

		case 2:
			h.intAff = 1;
			break;
	}
}


// permet de retourner l'évenement e
Evenement Jeu::gete(){

	return e;

}


//permet de retourner hacking h
Hacking Jeu::geth(){

	return h;

}


//permet d'effectuer une action selon la touche appuyer
void Jeu::actionClavier(const string touche){

	//si nous sommes dans l'évenement hacking
	if (e.getn() =="hack"){

		if (touche == "\n"){
			h.valider();
		}
		else{
			h.saisir(touche);
		}
	}

}
