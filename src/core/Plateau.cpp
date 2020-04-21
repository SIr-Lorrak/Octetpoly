#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------

//Crée le plateau (constructeur par défaut)
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	tabC[0].initCase('D',0,"Depart",0,0,0,0);
	tabC[1].initCase('E',5,"Auchan",10,1,1,5);
	tabC[2].initCase('E',5,"Aldi",10,1,1,5);
	tabC[3].initCase('E',15,"Carrefour",1,1,1,5);
	tabC[4].initCase('B',5,"Crédit agricole",4,0,0,5);
	tabC[5].initCase('E',20,"Arkane Studio",4,1,1,5);
	tabC[6].initCase('E',25,"Ankama",4,1,1,50);
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
	tabC[30].initCase('I',0,"Impot",50,0,0,0);
	tabC[31].initCase('E',100,"Google",4,1,1,2);

	casePub = 0;
}

//Destructeur de la classe
Plateau::~Plateau(){
	delete [] tabC;
}

//Permet de récupèrer l'adresse d'une case
Case * Plateau::getCase(unsigned int numCase) const{
	return &tabC[numCase];
}

void Plateau::setCase(unsigned int numCase,unsigned int p,unsigned int l,unsigned int prixdevente,unsigned int pM,unsigned int pB,unsigned int prop, int i){
	tabC[i].set(p,l,prixdevente,pM,pB,prop,i);
}


//Permet de récupérer la case qui est actuellement en campagne de pub
unsigned int Plateau::getcasePub() const {
	return casePub;
}
//---------------------------------Setters-------------------------------------------

//Permet de changer la valeur de setcasePub 
void Plateau::setcasePub(unsigned int numCase){
	casePub = numCase;
}

//-------------------------------------Méthodes------------------------------------------

	//Compte le nombre restant d'entreprise et de banque non-occupé
	unsigned int Plateau::nbCaseFree(){
		unsigned int nbcase = 0;
		for(unsigned int i = 0 ; i < TPLATEAU ; i++)
		{
			if(((tabC[i].getType() == 'E') 
				|| (tabC[i].getType() == 'B')) && 
				(tabC[i].getOccupation() == 0))
			{
				nbcase = nbcase + 1;
			}
		}
		return nbcase;
	}

	//Permet de recupérer l'indice d'une case entreprise ou banque par l'intermédiaire
	unsigned int Plateau::getIndice(const string & nom) const{
    	unsigned int i=0;
    	while(tabC[i].getNom()!=nom){
        	assert(i<32);//si i dépasse le nom envoyé est invalid
        	i++;
    	}
    	return i;
	}

	//Permet de vérifier si la case entreprise ou banque entrez par le joueur pour les portes ouvertes est disponible ou non 
	bool Plateau::caseValide(unsigned int choix,unsigned int joueur){
		bool valide = false;
		unsigned int i = 0;
		while(!valide && i < TPLATEAU )
		{
			if((tabC[i].getType() == 'B' || tabC[i].getType() == 'E')
				&& (tabC[i].getOccupation() == 0 || tabC[i].getOccupation() == joueur))
			{
				if(choix == i)
				{
					valide = true;
				}
			}
			i = i+1;
		}
		return valide;
	}

//-------------------------------------TEST REGRESSION-----------------------------------


	//Permet d'afficher toutes les données membre de la classe
	void Plateau::affichageRegression(){
		for(unsigned int i = 0; i < TPLATEAU ; i++)
		{
			cout << "CASE " << i << endl << endl;
		 	tabC[i].affichageRegression();
		 	cout << endl << endl;
		}

	}

	//Teste toutes les fonctions de la classe
	void Plateau::testRegressionPlateau(){
		//affichageRegression();
		/*
		cout << "Appel getCase() : ....." << endl;
		Case * c = getCase(6);
		cout << endl << "Case Appelé : " << c->getNom() << endl;
		c->affichageRegression();
		*/
		//cout << nbCaseFree() << endl;
		cout << casePub << endl;
		setcasePub(5);
		cout << casePub << endl;
		cout << getcasePub() << endl; 

	}

