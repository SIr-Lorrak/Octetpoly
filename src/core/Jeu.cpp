#include <assert.h>
#include <time.h>

#include "Jeu.h"

const string KONAMI_CODE[10] = {"^","^","v","v","<",">","<",">","b","a"};

bool estPasDans(const unsigned int n, const unsigned int tab[],const unsigned int taille = 4){
	if(taille == 0) return true;
	for(unsigned int i=0;i<taille;i++){
		if(tab[i]==n) return false;
	}
	return true;
}

//-------------------------------------Constructeurs---------------------------
Jeu::Jeu(){
	srand(time(NULL));
	attendreNom = false;
	desLance = false;
	avance = false;
	confirmation = false;
	nbJoueur = 0;
	nbTour = 0;
	unsigned int alea;
	for(unsigned int i=0;i<4;i++){
		do{
			alea = rand()%4+1;
		}while(!estPasDans(alea,ordre,i));
		ordre[i] = alea;
	}
	for(int i=0; i<10;i++){
		konami[i]=false;
	}
	coeffAd = 1;
}


//-------------------------------------Méthodes--------------------------------
void Jeu::getOrdre(unsigned int tab[4]) const
{
	for(int i =0; i<4 ; i++){ tab[i] = ordre[i];}
}

void Jeu::sauver(const string & file) const
{
	ofstream fichier(file.c_str());
	assert(fichier.is_open());
	//TODO
	
	fichier.close();
}

void Jeu::charger(const string & file)
{
	ifstream fichier(file.c_str());
	assert(fichier.is_open());
	//TODO
	
	fichier.close();
}

void Jeu::konamiCode(const string touche)
{
	//TODO
}


void Jeu::commencerPartie()
{
	tabO = new Ordi [4-nbJoueur];
	nbTour = 1;
	joueurCourant = ordre[0];
}


void Jeu::ajouterJoueur()
{
	tabJ[nbJoueur] = new Joueur;
	nbJoueur++;
	attendreNom = true;
}


void Jeu::ajouterLettre(const unsigned int n, const string lettre)
{
	tabJ[n]->ajouterLettre(lettre);
}

void Jeu::tourSuivant(){
	//TODO
}

void Jeu::actionClavier(const string touche)
{
	if(nbTour == 0){
		if(!attendreNom&&nbJoueur<4){
			if(touche == "+"){
				ajouterJoueur();
			}
			if(touche == "\n"){
				if(confirmation){
					commencerPartie();
					confirmation=false;
				}
				confirmation = true;
			}
		}
		else if(attendreNom){
			if(touche == "\n"){// \n c'est pour 'entrer' ou 'retour'
				attendreNom = false;
			}
			else if(touche != "\b"){// \b pour 'effacer'
				tabJ[nbJoueur]->ajouterLettre(touche);
			}
		}
	}
	else{
		konamiCode(touche);//pour le konami code
	}
	if(touche != "\n"){
		confirmation = false;
	}
}

//-------------------------------------Constructeurs--------------------------------------

Jeu::~Jeu(){
	delete [] tabO;
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}

//-------------------------------------Méthodes------------------------------------------

void faillite(){
	//TODO Enlever les propiété du joueur
	//TODO Le supprimer du tableau ordre
}

void Jeu::paye(unsigned int payeur, unsigned int creancier, float montant){
	assert((payeur <= 4 || payeur > 0) && (creancier <= 4 || creancier > 0));
	//Echange entre ordi
	if(payeur > nbJoueur && payeur > creancier)
	{
		unsigned int coinP = tabO[payeur-1].getCoin();
		unsigned int coinC = tabO[creancier-1].getCoin();
		tabO[payeur-1].setCoin(coinP-montant);
		tabO[creancier-1].setCoin(coinC-montant);
	}
	
	//Le payeur est un joueur ; Le creancier est un ordi
	else if(payeur <= nbJoueur && payeur > creancier)
	{
		unsigned int coinP = tabJ[payeur-1]->getCoin();
		unsigned int coinC = tabO[creancier-1].getCoin();
		tabJ[payeur-1]->setCoin(coinP-montant);
		tabO[creancier-1].setCoin(coinC-montant);
	}
	
	//Le payeur est un ordi ; Le creancier est un joueur
	else if(payeur > nbJoueur && payeur <= creancier)
	{
		unsigned int coinP = tabO[payeur-1].getCoin();
		unsigned int coinC = tabJ[creancier-1]->getCoin();
		tabO[payeur-1].setCoin(coinP-montant);
		tabJ[creancier-1]->setCoin(coinC-montant);	
	}
	//Echange entre joueur
	else
	{
		unsigned int coinP = tabJ[payeur-1]->getCoin();
		unsigned int coinC = tabJ[creancier-1]->getCoin();
		tabJ[payeur-1]->setCoin(coinP-montant);
		tabJ[creancier-1]->setCoin(coinC-montant);
	}
}

void Jeu::payeLoyer(){
	
//C'est un ordi qui joue	
	if(tourOrdi)
	{
		//La case où se trouve le joueurCourant
		Case * c = board.getCase(tabO[joueurCourant-1].getPos());

		//Le joueurCourant paye directement si il a assez d'argent 
		if(coinCourant >= c->getLoyer())
		{
		paye(joueurCourant,c->getOccupation(),c->getLoyer());
		}

		//Le joueurCourant doit vendre pour payer le loyer
		if((coinCourant + tabO[joueurCourant-1].patrimoineActif()) >= c->getLoyer())
		{
			paye(joueurCourant,c->getOccupation(),c->getLoyer());
			while(coinCourant < 0)
			{
				tabO[joueurCourant-1].vendre();
			}
		}
		else
		{
			//faillite
		}
	}

//C'est un joueur qui joue	
	else
	{
		//La case où se trouve le joueurCourant
		Case * c = board.getCase(tabJ[joueurCourant-1]->getPos());

		//Le joueurCourant paye directement si il a assez d'argent 
		if(coinCourant >= c->getLoyer())
		{
			paye(joueurCourant,c->getOccupation(),c->getLoyer());
		}

		//Le joueurCourant doit vendre pour payer le loyer
		if((coinCourant + tabJ[joueurCourant-1]->patrimoineActif()) >= c->getLoyer())
		{
			paye(joueurCourant,c->getOccupation(),c->getLoyer());
			while(tabJ[joueurCourant-1]->getCoin() < 0)
			{
				tabJ[joueurCourant-1]->vendre();
			}
		}
		else
		{
			//faillite
		}
	}
}

void Jeu::investirEOrdi(){
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(tabO[joueurCourant-1].getPos());

	//Est-ce que le joueurCourant veux investir
	int investi = tabO[joueurCourant-1].AIinvesti(*c);

	//Est-ce que le joueurCourant a assez d'argent
	if(investi == 1 && coinCourant >= c->getPrixB())
	{
		c->investir(1);
		tabO[joueurCourant-1].setCoin(coinCourant - c->getPrixB());
	}

	//Est-ce que le joueurCourant a assez d'argent
	else if (investi == -1 && coinCourant >= c->getPrixM())
	{
		c->investir(-1);
		tabO[joueurCourant-1].setCoin(coinCourant - c->getPrixM());
	}
}

void Jeu::actionBEOrdi(){

	//La case où se trouve le joueurCourant
	Case * c = board.getCase(tabO[joueurCourant-1].getPos());

	//A quel joueur appartient la case
	unsigned int occupant = c->getOccupation();

	//L'argent actuel du joueurCourant
	unsigned int coinCourant = tabO[joueurCourant-1].getCoin();

//Vérifie si la case n'appartient pas au joueurCourant
	if(occupant != joueurCourant)
	{											 
		switch(occupant)//Différent cas de figure
		{
			case 0://N'appartient à personne,le joueurCourant peut acheter la banque

					//Est-ce que le joueurCourant veut acheter
					//Et est-ce qu'il a assez d'argent pour
					if(tabO[joueurCourant-1].AIacheteEntreprise(*c)
						&& coinCourant >= c->getPrixInitial())
					{
						tabO[joueurCourant-1].acheter(c);

						//Investissement uniquement possible pour une entreprise
						if(c->getType() == 'E')
						{
							investirEOrdi();
						}
					}

				break;

			case 1:
				payeLoyer();
				//On met à jour la variable coinCourant 
				coinCourant = tabO[joueurCourant-1].getCoin();
				break;

			case 2:
				payeLoyer();
				//On met à jour la variable coinCourant 
				coinCourant = tabO[joueurCourant-1].getCoin();
				break;

			case 3:
				payeLoyer();
				//On met à jour la variable coinCourant 
				coinCourant = tabO[joueurCourant-1].getCoin();
				break;

			case 4:
				payeLoyer();
				//On met à jour la variable coinCourant 
				coinCourant = tabO[joueurCourant-1].getCoin();
				break;

			default:
				//assert(false);
				break;
		}
	}
//La case appartient à l'ordi	
//Si c'est une entreprise, il pourra peut-être investir
	else if (c->getType() == 'E')
	{
		investirEOrdi();
	}
}

void Jeu::banque(){
	if(tourOrdi)
	{
		actionBEOrdi();
	}
	else
	{

	}
}

void Jeu::entreprise(){
	//C'est un ordi qui joue
	if(tourOrdi)
	{
		actionBEOrdi();
	}	
	else
	{

	}		
				
}

void Jeu::prison(){
	//if (tabO[joueurCourant-1]) 
}

void Jeu::carteChance(){
	
}

void Jeu::campagneDePub(){
//C'est un ordi qui joue	
	if(tourOrdi)
	{	
		//La case où se trouve le joueurCourant
		Case * c = board.getCase(tabO[joueurCourant-1].getPos());

		if(coinCourant >= c->getPrix())
		{	
			unsigned int quelleCase = tabO[joueurCourant-1].AIchampionat();
			 
			if (quelleCase == casePub)
			{
				coeffAd++;
				Case * championnat = board.getCase(quelleCase);
				championnat->advertising(coeffAd);
			}
			else
			{
				if (casePub >= 0)
				{
					Case * exChampionnat = board.getCase(casePub);
					exChampionnat->endAdvertising(coeffAd);

					casePub = quelleCase;
					coeffAd = 2;
					Case * championnat = board.getCase(quelleCase);
					championnat->advertising(2);
				}
				else
				{	
					casePub = quelleCase;
					coeffAd = 2;
					Case * championnat = board.getCase(quelleCase);
					championnat->advertising(coeffAd);
				}
			}

			tabO[joueurCourant-1].setCoin(coinCourant - c->getPrix());
		} 
		
	}
//C'est un joueur qui joue	
	else
	{

	}
}

void Jeu::porteOuverte(){
	
}


//A mettre dans jeu 
void Jeu::actionCase(const string touche){

	//La case où se trouve le joueurCourant
	Case * c = board.getCase(tabO[joueurCourant-1].getPos());

	switch(c->getType()){
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

		case 'P':
			prison();
			break;
	}
}
