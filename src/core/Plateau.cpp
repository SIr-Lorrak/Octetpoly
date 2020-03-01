#include "Plateau.h"

using namespace std;

//-------------------------------------Constructeur--------------------------------------
Plateau::Plateau(){
	nbcase = TPLATEAU;
	tabC = new Case[nbcase];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt
	tabC[0].settype('D');
	tabC[1].settype('E');
	tabC[2].settype('E');
	tabC[3].settype('E');
	tabC[4].settype('B');
	tabC[5].settype('E');
	tabC[6].settype('E');
	tabC[7].settype('E');
	tabC[8].settype('P');

	tabC[9].settype('E');
	tabC[11].settype('E');
	tabC[12].settype('C');
	tabC[13].settype('E');
	tabC[14].settype('B');
	tabC[15].settype('E');

	tabC[16].settype('?');
	tabC[17].settype('E');
	tabC[18].settype('E');
	tabC[19].settype('E');
	tabC[20].settype('C');
	tabC[21].settype('E');
	tabC[22].settype('B');
	tabC[23].settype('E');
	tabC[24].settype('?');

	tabC[25].settype('B');
	tabC[26].settype('E');
	tabC[27].settype('E');
	tabC[28].settype('C');
	tabC[29].settype('E');
	tabC[30].settype('I');
	tabC[31].settype('E');

	nbJoueur = 0;
	//tabJ = new Joueur[nbJoueur];
	nbOrdi = 0;
	//tabO = new Ordi[nbOrdi];
	
	dimx = 0;
	dimy = 0;
}


Plateau::Plateau(const unsigned int dimensionX, const unsigned int dimensionY, const unsigned int nombreDeJoueur){

	nbcase = TPLATEAU;
	tabC = new Case[nbcase];

	//D : Départ ; E : Entreprise ; B : Banque ; P : Prison ; C : Chance ; I : Impôt
	tabC[0].settype('D');
	tabC[1].settype('E');
	tabC[2].settype('E');
	tabC[3].settype('E');
	tabC[4].settype('B');
	tabC[5].settype('E');
	tabC[6].settype('E');
	tabC[7].settype('E');
	tabC[8].settype('P');

	tabC[9].settype('E');
	tabC[11].settype('E');
	tabC[12].settype('C');
	tabC[13].settype('E');
	tabC[14].settype('B');
	tabC[15].settype('E');

	tabC[16].settype('?');
	tabC[17].settype('E');
	tabC[18].settype('E');
	tabC[19].settype('E');
	tabC[20].settype('C');
	tabC[21].settype('E');
	tabC[22].settype('B');
	tabC[23].settype('E');
	tabC[24].settype('?');

	tabC[25].settype('B');
	tabC[26].settype('E');
	tabC[27].settype('E');
	tabC[28].settype('C');
	tabC[29].settype('E');
	tabC[30].settype('I');
	tabC[31].settype('E');

	nbJoueur = nombreDeJoueur;
	//tabJ = new Joueur[nbJoueur];
	nbOrdi = 4 - nbJoueur;
	//tabO = new Ordi[nbOrdi];

	dimx = dimensionX;
	dimy = dimensionY;
}

Plateau::~Plateau(){
	//TODO
}


