#include "Plateau.h"
#include "assert.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	tabC[0].initCase('D',0,"Depart");
	tabC[1].initCase('E',5,"Auchan");
	tabC[2].initCase('E',10,"Aldi");
	tabC[3].initCase('E',15,"Carrefour");
	tabC[4].initCase('B',5,"Crédit agricole");
	tabC[5].initCase('E',20,"Arkane Studio");
	tabC[6].initCase('E',25,"Ankama");
	tabC[7].initCase('E',30,"Ubisof");
	tabC[8].initCase('P',15,"Prison");

	tabC[9].initCase('E',35,"Shell");
	tabC[10].initCase('E',40,"Total");
	tabC[11].initCase('E',45,"Exxon");
	tabC[12].initCase('C',0,"Chance");
	tabC[13].initCase('E',50,"Peugeot");
	tabC[14].initCase('B',5,"BNB Paribas");
	tabC[15].initCase('E',55,"Toyota");

	tabC[16].initCase('A',15,"Campagne de pub");
	tabC[17].initCase('E',60,"Bayer");
	tabC[18].initCase('B',5,"HSBC");
	tabC[19].initCase('E',65,"Sanofi");
	tabC[20].initCase('C',0,"Chance");
	tabC[21].initCase('E',70,"Nintendo");
	tabC[22].initCase('E',75,"Sony");
	tabC[23].initCase('E',80,"Microsoft");
	tabC[24].initCase('O',15,"Porte Ouverte");

	tabC[25].initCase('B',5,"Bank of china");
	tabC[26].initCase('E',85,"Samsung");
	tabC[27].initCase('E',90,"Apple");
	tabC[28].initCase('C',0,"Chance");
	tabC[29].initCase('E',95,"Amazon");
	tabC[30].initCase('I',0,"Impot");
	tabC[31].initCase('E',100,"Google");
}

Plateau::~Plateau(){
	//TODO
	delete [] tabC;
}

//-------------------------------------Méthodes--------------------------------
Case * Plateau::getCase(unsigned int numCase) const{
	return &tabC[numCase];
}

unsigned int Plateau::getIndice(const string & nom) const{
	unsigned int i=0;
	while(tabC[i].getNom()!=nom){
		i++;
		assert(i>=32);//si i dépasse le nom envoyé est invalid
	}
	return i;
}