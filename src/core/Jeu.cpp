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
	//TODO Enlever les propièté du joueur
	//TODO Le supprimer du tableau ordre
}

void Jeu::banque(Case * c){
	if(tourOrdi)
	{
		unsigned int occupant = c->getOccupation();
		unsigned int coin = tabO[joueurCourant-1].getCoin();
		if(occupant != joueurCourant)//Vérifie si ça n'appartient
		{											 //pas au joueur
			switch(occupant)//Différent cas de figure
			{
				case 0:
						if(tabO[joueurCourant-1].AIacheteEntreprise(*c)
							&& coin >= c->getPrixInitial())
						{
							c->estAcheter(joueurCourant);
							//TODO enlever l'argent du joueur
						}
					break;

				case 1:
					if(coin >= c->getLoyer())
					{
						//TODO le joueur paye le joueur1
					}
					else if(true)
					{

					}
					else
					{

					}
					break;

				case 2:
					
					break;

				case 3:
					
					break;

				case 4:
					
					break;
			}
		}
	}
}

void Jeu::entreprise(Case * c){
	/*
	else 
	{
		int investissement = tabO[joueurCourant-1].AIinvesti(*c);
		if (investissement == -1 && coin >= c->getPrixM())
		{
				c->investir(investissement);
				//TODO Enlever l'argent de l'ordi
		}
	}
	else
	{

	}
	*/
}

void Jeu::prison(){
	
}

void Jeu::carteChance(){
	
}

void Jeu::campagneDePub(Case * c){
	unsigned int coin = tabO[joueurCourant-1].getCoin();
	if(coin >= 50000)
	{
		bool deuxiemePub = c->getAd();
		if (deuxiemePub)
		{
			//TODO loyer augmenter !
		}
		else
		{
			c->advertising(tabO[joueurCourant-1].AIchampionat());
		}
	//TODO enlever l'argent du joueur	
	}
	
}

void Jeu::porteOuverte(){
	
}


//A mettre dans jeu 
void Jeu::actionCase(unsigned int num){
	Case c = *board.getCase(num);
	switch(c.getType()){
		case 'E':
			entreprise(&c);
			break;

		case 'B':
			banque(&c);
			break;

		case 'C':
			carteChance();
			break;

		case 'A':
			campagneDePub(&c);
			break;

		case 'O':
			porteOuverte();
			break;

		case 'I':
			//TODO 
			break;

		case 'D':
			//TODO
			break;

		case 'P':
			prison();
			break;
	}
}
