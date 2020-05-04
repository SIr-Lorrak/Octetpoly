#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------

//Crée le plateau (constructeur par défaut)
Plateau::Plateau(){
	tabC = new Case[TPLATEAU];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt 
	//O : Porte Ouverte ; A : Publicité (Advertising)
	//Initialisation des cases au lancement d'une partie 
	//Dans l'ordre suivant
	//(groupe ; type ; prix ; nom ; karmaCase ; prixDeVente ; prixMauvais ; 
	//prixBon ; loyer ; coeffUn ; coeffDeux ; coeffTrois ; coeffQuatre ; coeffCinq)
	tabC[0].initCase(0,'D',0,"Depart",0,0,0,0,0,0,0,0,0,0);
	tabC[1].initCase(1,'E',6000,"Auchan",10,3000,3000,5000,200,5,3,3,1.77,1.56);
	tabC[2].initCase(1,'E',6000,"Aldi",10,3000,3000,5000,200,5,3,3,1.77,1.56);
	tabC[3].initCase(1,'E',6000,"Carrefour",5,3000,3000,5000,400,5,3,3,1.77,1.4);
	tabC[4].initCase(42,'B',20000,"Crédit agricole",0,10000,0,0,8500,0,0,0,0,0);
	tabC[5].initCase(2,'E',10000,"Arkane Studio",10,5000,3000,5000,600,5,3,3,1.48,1.37);
	tabC[6].initCase(2,'E',10000,"Ankama",10,5000,3000,5000,600,5,3,3,1.48,1.37);
	tabC[7].initCase(2,'E',12000,"Ubisoft",10,6000,3000,5000,800,5,2.5,3,1.5,1.33);
	tabC[8].initCase(0,'P',5000,"Prison",0,0,0,0,0,0,0,0,0,0);

	tabC[9].initCase(3,'E',14000,"Shell",15,7000,8000,10000,1000,5,3,3,1.38,1.2);
	tabC[10].initCase(3,'E',14000,"Total",15,7000,8000,10000,1000,5,3,3,1.38,1.2);
	tabC[11].initCase(3,'E',16000,"Exxon",15,8000,8000,10000,1200,5,3,2.77,1.4,1.28);
	tabC[12].initCase(0,'C',0,"Chance",0,0,0,0,0,0,0,0,0,0);
	tabC[13].initCase(4,'E',18000,"Peugeot",20,9000,8000,10000,1400,5,2.85,2.75,1.37,1.26);
	tabC[14].initCase(42,'B',20000,"BNB Paribas",0,10000,1,1,8500,0,0,0,0,0);
	tabC[15].initCase(4,'E',20000,"Toyota",20,10000,8000,10000,1600,5,2.75,2.72,1.33,1.25);

	tabC[16].initCase(0,'A',25000,"Campagne de pub",0,0,0,0,0,0,0,0,0,0);
	tabC[17].initCase(5,'E',22000,"Bayer",25,11000,13000,15000,1800,5,2.77,2.8,1.25,1.2);
	tabC[18].initCase(42,'B',20000,"HSBC",0,10000,1,1,8500,0,0,0,0,0);
	tabC[19].initCase(5,'E',24000,"Sanofi",25,12000,13000,15000,2000,5,3,2.5,1.23,1.18);
	tabC[20].initCase(0,'C',0,"Chance",0,0,0,0,0,0,0,0,0,0);
	tabC[21].initCase(6,'E',26000,"Nintendo",30,13000,13000,15000,2200,5,3,2.42,1.21,1.17);
	tabC[22].initCase(6,'E',26000,"Sony",30,13000,13000,15000,2200,5,3,2.42,1.21,1.17);
	tabC[23].initCase(6,'E',28000,"Microsoft",30,14000,13000,15000,2400,5,3,2.36,1.2,1.17);
	tabC[24].initCase(0,'O',25000,"Porte Ouverte",0,0,0,0,0,0,0,0,0,0);

	tabC[25].initCase(42,'B',20000,"Bank of china",0,10000,1,1,8500,0,0,0,0,0);
	tabC[26].initCase(7,'E',30000,"Samsung",35,15000,18000,20000,2600,5,3,2.3,1.22,1.15);
	tabC[27].initCase(7,'E',32000,"Apple",35,16000,18000,20000,2800,5.35,3,2.22,1.2,1.16);
	tabC[28].initCase(0,'C',0,"Chance",0,4,1,1,2,0,0,0,0,0);
	tabC[29].initCase(8,'E',35000,"Amazon",40,17500,18000,20000,3500,5,2.87,2.2,1.18,1.15);
	tabC[30].initCase(0,'I',10000,"Impot",0,50,0,0,0,0,0,0,0,0);
	tabC[31].initCase(8,'E',40000,"Google",40,20000,18000,20000,5000,4,3,2.33,1.21,1.17);

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


//Permet de set les différents attributs variables d'une case (lors du chargement d'une partie).
void Plateau::setCase(unsigned int numCase,unsigned int p,unsigned int l,unsigned int prixdevente,unsigned int pM,unsigned int pB,unsigned int prop, int i){
	tabC[numCase].set(p,l,prixdevente,pM,pB,prop,i);
}


//Permet de récupérer la case qui est actuellement en campagne de pub
unsigned int Plateau::getcasePub() const {
	return casePub;
}
//---------------------------------Setters-------------------------------------------

//Permet de changer la valeur de casePub 
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

	//Permet de récupérer l'indice d'une case entreprise ou banque par l'intermédiaire de son nom
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

