#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	tabC[0].initCase('D',0,"Depart",0,0,0,0);
	tabC[1].initCase('E',5,"Auchan",4,1,1,2);
	tabC[2].initCase('E',10,"Aldi",4,1,1,2);
	tabC[3].initCase('E',15,"Carrefour",4,1,1,2);
	tabC[4].initCase('B',5,"Crédit agricole",4,0,0,2);
	tabC[5].initCase('E',20,"Arkane Studio",4,1,1,2);
	tabC[6].initCase('E',25,"Ankama",4,1,1,2);
	tabC[7].initCase('E',30,"Ubisof",4,1,1,2);
	tabC[8].initCase('P',15,"Prison",0,0,0,0);

	tabC[9].initCase('E',35,"Shell",4,1,1,2);
	tabC[10].initCase('E',40,"Total",4,1,1,2);
	tabC[11].initCase('E',45,"Exxon",4,1,1,2);
	tabC[12].initCase('C',0,"Chance",0,0,0,0);
	tabC[13].initCase('E',50,"Peugeot",4,1,1,2);
	tabC[14].initCase('B',5,"BNB Paribas",4,1,1,2);
	tabC[15].initCase('E',55,"Toyota",4,1,1,2);

	tabC[16].initCase('A',15,"Campagne de pub",0,0,0,0);
	tabC[17].initCase('E',60,"Bayer",4,1,1,2);
	tabC[18].initCase('B',5,"HSBC",4,1,1,2);
	tabC[19].initCase('E',65,"Sanofi",4,1,1,2);
	tabC[20].initCase('C',0,"Chance",0,0,0,0);
	tabC[21].initCase('E',70,"Nintendo",4,1,1,2);
	tabC[22].initCase('E',75,"Sony",4,1,1,2);
	tabC[23].initCase('E',80,"Microsoft",4,1,1,2);
	tabC[24].initCase('O',15,"Porte Ouverte",0,0,0,0);

	tabC[25].initCase('B',5,"Bank of china",4,1,1,2);
	tabC[26].initCase('E',85,"Samsung",4,1,1,2);
	tabC[27].initCase('E',90,"Apple",4,1,1,2);
	tabC[28].initCase('C',0,"Chance",4,1,1,2);
	tabC[29].initCase('E',95,"Amazon",4,1,1,2);
	tabC[30].initCase('I',0,"Impot",0,0,0,0);
	tabC[31].initCase('E',100,"Google",4,1,1,2);
}

Plateau::~Plateau(){
	//TODO
	delete [] tabC;
}

//-------------------------------------Méthodes--------------------------------
Case * Plateau::getCase(unsigned int numCase){
	return &tabC[numCase];
}

//-------------------------------------TEST REGRESSION-----------------------------------

	/**
	@brief Permet d'afficher toutes les données membre de la classe
	@param none
	*/
	void Plateau::affichageRegression(){
		for(unsigned int i = 0; i < TPLATEAU ; i++)
		{
			cout << "CASE " << i << endl << endl;
		 	tabC[i].affichageRegression();
		 	cout << endl << endl;
		}

	}

	/**
	@brief Teste toutes les fonctions de la classe
	@param none
	*/
	void Plateau::testRegressionPlateau(){
		affichageRegression();

		cout << "Appel getCase() : ....." << endl;
		Case * c = getCase(6);
		cout << endl << "Case Appelé : " << c->getNom() << endl;
		c->affichageRegression();
	}

