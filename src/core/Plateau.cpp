#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	tabC[0].initCase('D',0,0);
	tabC[1].initCase('E',0,0);
	tabC[2].initCase('E',0,0);
	tabC[3].initCase('E',0,0);
	tabC[4].initCase('B',0,0);
	tabC[5].initCase('E',0,0);
	tabC[6].initCase('E',0,0);
	tabC[7].initCase('E',0,0);
	tabC[8].initCase('P',0,0);

	tabC[9].initCase('E',0,0);
	tabC[11].initCase('E',0,0);
	tabC[12].initCase('E',0,0);
	tabC[13].initCase('C',0,0);
	tabC[14].initCase('E',0,0);
	tabC[15].initCase('B',0,0);
	tabC[16].initCase('E',0,0);

	tabC[17].initCase('A',0,0);
	tabC[18].initCase('E',0,0);
	tabC[19].initCase('B',0,0);
	tabC[20].initCase('C',0,0);
	tabC[21].initCase('E',0,0);
	tabC[22].initCase('E',0,0);
	tabC[23].initCase('E',0,0);
	tabC[24].initCase('O',0,0);

	tabC[25].initCase('B',0,0);
	tabC[26].initCase('E',0,0);
	tabC[27].initCase('E',0,0);
	tabC[28].initCase('C',0,0);
	tabC[29].initCase('E',0,0);
	tabC[30].initCase('I',0,0);
	tabC[31].initCase('E',0,0);
}

Plateau::~Plateau(){
	//TODO
}

//-------------------------------------Méthodes--------------------------------
Case & Plateau::getCase(){

}

void Plateau::reset(){

}

