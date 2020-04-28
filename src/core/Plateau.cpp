#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------

//Crée le plateau (constructeur par défaut)
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	tabC[0].initCase(0,'D',0,"Depart",0,0,0,0,0);
	tabC[1].initCase(1,'E',5,"Auchan",5,1000,1,1,5);
	tabC[2].initCase(1,'E',25,"Aldi",5,5,1,1,5);
	tabC[3].initCase(1,'E',15,"Carrefour",5,1,1,1,5);
	tabC[4].initCase(42,'B',5,"Crédit agricole",0,4,0,0,5);
	tabC[5].initCase(2,'E',20,"Arkane Studio",10,4,1,1,5);
	tabC[6].initCase(2,'E',25,"Ankama",10,4,1,1,50);
	tabC[7].initCase(2,'E',30,"Ubisof",10,4,1,1,2);
	tabC[8].initCase(0,'P',15,"Prison",0,0,0,0,0);

	tabC[9].initCase(3,'E',35,"Shell",15,4,1,1,2);
	tabC[10].initCase(3,'E',40,"Total",15,4,1,1,2);
	tabC[11].initCase(3,'E',45,"Exxon",15,4,1,1,2);
	tabC[12].initCase(0,'C',0,"Chance",0,0,0,0,0);
	tabC[13].initCase(4,'E',50,"Peugeot",20,4,1,1,2);
	tabC[14].initCase(42,'B',5,"BNB Paribas",0,4,1,1,2);
	tabC[15].initCase(4,'E',55,"Toyota",20,4,1,1,2);

	tabC[16].initCase(0,'A',15,"Campagne de pub",0,0,0,0,0);
	tabC[17].initCase(5,'E',60,"Bayer",25,4,1,1,2);
	tabC[18].initCase(42,'B',5,"HSBC",0,4,1,1,2);
	tabC[19].initCase(5,'E',65,"Sanofi",25,4,1,1,2);
	tabC[20].initCase(0,'C',0,"Chance",0,0,0,0,0);
	tabC[21].initCase(6,'E',70,"Nintendo",30,4,1,1,2);
	tabC[22].initCase(6,'E',75,"Sony",30,4,1,1,2);
	tabC[23].initCase(6,'E',80,"Microsoft",30,4,1,1,2);
	tabC[24].initCase(0,'O',15,"Porte Ouverte",0,0,0,0,0);

	tabC[25].initCase(42,'B',5,"Bank of china",0,4,1,1,2);
	tabC[26].initCase(7,'E',85,"Samsung",35,4,1,1,2);
	tabC[27].initCase(7,'E',90,"Apple",35,4,1,1,2);
	tabC[28].initCase(0,'C',0,"Chance",0,4,1,1,2);
	tabC[29].initCase(8,'E',95,"Amazon",40,4,1,1,2);
	tabC[30].initCase(0,'I',5,"Impot",0,50,0,0,0);
	tabC[31].initCase(8,'E',100,"Google",40,4,1,1,2);

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

	//Permet de recupérer l'indice d'une case entreprise ou banque par l'intermédiaire de son nom
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

