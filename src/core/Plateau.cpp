#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	tabC[0].initCase('D',0);
	tabC[1].initCase('E',5);
	tabC[2].initCase('E',10);
	tabC[3].initCase('E',15);
	tabC[4].initCase('B',5);
	tabC[5].initCase('E',20);
	tabC[6].initCase('E',25);
	tabC[7].initCase('E',30);
	tabC[8].initCase('P',20);

	tabC[9].initCase('E',35);
	tabC[11].initCase('E',40);
	tabC[12].initCase('E',45);
	tabC[13].initCase('C',0);
	tabC[14].initCase('E',50);
	tabC[15].initCase('B',5);
	tabC[16].initCase('E',55);

	tabC[17].initCase('A',10);
	tabC[18].initCase('E',60);
	tabC[19].initCase('B',5);
	tabC[20].initCase('C',0);
	tabC[21].initCase('E',65);
	tabC[22].initCase('E',70);
	tabC[23].initCase('E',75);
	tabC[24].initCase('O',10);

	tabC[25].initCase('B',5);
	tabC[26].initCase('E',80);
	tabC[27].initCase('E',85);
	tabC[28].initCase('C',0);
	tabC[29].initCase('E',90);
	tabC[30].initCase('I',0);
	tabC[31].initCase('E',95);
}

Plateau::~Plateau(){
	//TODO
	delete [] tabC;
}

//-------------------------------------Méthodes--------------------------------
Case * Plateau::getCase(unsigned int numCase){
	return &tabC[numCase];
}

/*
void Plateau::reset(){

}
*/

