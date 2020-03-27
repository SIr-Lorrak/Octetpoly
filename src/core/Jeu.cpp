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
	nbJoueur = 1;
	nbTour = 0;
	tabO = new Ordi[0];
	unsigned int alea;
	for(unsigned int i=0;i<4;i++){
		do{
			alea = rand()%4+1;
		}while(!estPasDans(alea,ordre,i));
		ordre[i] = alea;
	}
	for(unsigned int i=0; i<10;i++){
		konami[i]=false;
	}

	coeffAd = 1;
	joueurCourant = 1;
	coinCourant = 500;
	casePub = 0;
	tourOrdi =false;
	tabJ[0] = new Joueur;
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

//-------------------------------------Destructeurs--------------------------------------

Jeu::~Jeu(){
	delete [] tabO;
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}

//-------------------------------------Méthodes------------------------------------------

Joueur * Jeu::getJoueur(const unsigned int i) const
{
    assert(nbJoueur>=i);
    return tabJ[i-1];
}

Ordi * Jeu::getOrdi(const unsigned int i) const
{
    assert(nbJoueur<i);
    return &tabO[i-nbJoueur-1];
}

Pion * Jeu::getPion(const unsigned int i) const
{
    assert(i<=4&&i>0);
    if(i<=nbJoueur){
        return getJoueur(i)->getPion();
    }

    else{
        return getOrdi(i)->getPion();
    }
}

void Jeu::paye(unsigned int payeur, unsigned int creancier, float montant){
	assert((payeur <= 4 || payeur > 0) && (creancier <= 4 || creancier > 0));
	//Echange entre ordi
	if(payeur > nbJoueur && creancier > nbJoueur)
	{
		unsigned int coinP = tabO[payeur-1].getCoin();
		unsigned int coinC = tabO[creancier-1].getCoin();
		tabO[payeur-1].setCoin(coinP-montant);
		tabO[creancier-1].setCoin(coinC+montant);
	}

	//Le payeur est un joueur ; Le creancier est un ordi
	else if(payeur <= nbJoueur && creancier > nbJoueur)
	{
		unsigned int coinP = tabJ[payeur-1]->getCoin();
		unsigned int coinC = tabO[creancier-1].getCoin();
		tabJ[payeur-1]->setCoin(coinP-montant);
		tabO[creancier-1].setCoin(coinC+montant);
	}
	
	//Le payeur est un ordi ; Le creancier est un joueur
	else if(payeur > nbJoueur && creancier <= nbJoueur)
	{
		unsigned int coinP = tabO[payeur-1].getCoin();
		unsigned int coinC = tabJ[creancier-1]->getCoin();
		tabO[payeur-1].setCoin(coinP-montant);
		tabJ[creancier-1]->setCoin(coinC+montant);	
	}
	//Echange entre joueur
	else
	{
		unsigned int coinP = tabJ[payeur-1]->getCoin();
		unsigned int coinC = tabJ[creancier-1]->getCoin();
		tabJ[payeur-1]->setCoin(coinP-montant);
		tabJ[creancier-1]->setCoin(coinC+montant);
	}
}

void Jeu::pub(unsigned int quelleCase){
	if (quelleCase == casePub)
	{
		coeffAd++;
		Case * championnat = board.getCase(casePub);
		championnat->advertising(coeffAd);

	}
	else
	{
		if (casePub == 0)
		{
			Case * exChampionnat = board.getCase(casePub);
			exChampionnat->endAdvertising(coeffAd);

			casePub = quelleCase;
			coeffAd = 2;
			Case * championnat = board.getCase(quelleCase);
			championnat->advertising(coeffAd);
		}
		else
		{	
			casePub = quelleCase;
			coeffAd = 2;
			Case * championnat = board.getCase(quelleCase);
			championnat->advertising(coeffAd);
		}		
	} 
}

void Jeu::payeLoyerJoueur(){
//C'est un joueur qui joue	
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	//Le joueurCourant paye directement si il a assez d'argent 
	if(coinCourant >= c->getLoyer())
	{
		paye(joueurCourant,c->getOccupation(),c->getLoyer());
	}

	//Le joueurCourant doit vendre pour payer le loyer
	else if((coinCourant + getPion(joueurCourant)->patrimoineActif()) >= c->getLoyer())
	{
		paye(joueurCourant,c->getOccupation(),c->getLoyer());
		while(getPion(joueurCourant)->getCoin() < 0)
		{
			getPion(joueurCourant)->vendre();
		}
	}
	else
	{
		//faillite
	}
}

void Jeu::investirEJoueur(const string touche){
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	//Est-ce que le joueurCourant veux investir
	//Est-ce que le joueurCourant a assez d'argent
	if(touche == "+" && coinCourant >= c->getPrixB())
	{
		getPion(joueurCourant)->setCoin(coinCourant - c->getPrixB());
		c->investir(1);
	}

	//Est-ce que le joueurCourant a assez d'argent
	else if (touche == "-" && coinCourant >= c->getPrixM())
	{
		getPion(joueurCourant)->setCoin(coinCourant - c->getPrixM());
		c->investir(-1);
	}
}

void Jeu::actionBE(const string touche){

	//La case où se trouve le JOUEUR
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	//A quel joueur appartient la case
	unsigned int occupant = c->getOccupation();

	//L'argent actuel du JOUEUR
	unsigned int coinCourant = getPion(joueurCourant)->getCoin();

//Vérifie si la case n'appartient pas au JOUEUR
	if(occupant != joueurCourant)
	{											 
		switch(occupant)//Différent cas de figure
		{
			case 0://N'appartient à personne,le JOUEUR peut acheter la banque
					//Est-ce que le JOUEUR veut acheter
					//Et est-ce qu'il a assez d'argent pour
					if((touche == "o" ||touche == "O" || touche == "enter") && coinCourant >= c->getPrixInitial())
					{
						getPion(joueurCourant)->acheter(c);
						
						//Investissement uniquement possible pour une entreprise
						if(c->getType() == 'E')
						{
							investirEJoueur(touche);
							coinCourant = getPion(joueurCourant)->getCoin();
						}
					}

				break;

			case 1:
				payeLoyerJoueur();
				//On met à jour la variable coinCourant 
				coinCourant = getPion(joueurCourant)->getCoin();
				break;

			case 2:
				payeLoyerJoueur();
				//On met à jour la variable coinCourant 
				coinCourant = getPion(joueurCourant)->getCoin();
				break;

			case 3:
				payeLoyerJoueur();
				//On met à jour la variable coinCourant 
				coinCourant = getPion(joueurCourant)->getCoin();
				break;

			case 4:
				payeLoyerJoueur();
				//On met à jour la variable coinCourant 
				coinCourant = getPion(joueurCourant)->getCoin();
				break;

			default:
				assert(false);
				break;
		}
	}
//La case appartient au JOUEUR	
//Si c'est une entreprise, il pourra peut-être investir
	else if (c->getType() == 'E')
	{
		investirEJoueur(touche);
	}
}

//-------------------------------------Cases Du plateau----------------------------------

void Jeu::banque(const string touche){
	if(!tourOrdi)
	{
		actionBE(touche);
	}
}

void Jeu::entreprise(const string touche){
	if(!tourOrdi)
	{
		actionBE(touche);
	}				
}

void Jeu::prison(){
	//TODO
}

void Jeu::carteChance(){
	//TODO
}

void Jeu::campagneDePub(const string touche){
	Case * c = board.getCase(16);//ATTENTION APPEL FRAUDULEUX
	if(coinCourant >= c->getPrix())
	{
		unsigned int Case = 1;//TODO
		pub(Case);
		getPion(joueurCourant)->setCoin(coinCourant - c->getPrix());	
	}
	
}

void Jeu::porteOuverte(){
	
}

void Jeu::actionCase(const string touche){

	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	switch(c->getType()){
		case 'E':
			entreprise(touche);
			break;

		case 'B':
			banque(touche);
			break;

		case 'C':
			carteChance();
			break;

		case 'A':
			campagneDePub(touche);
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
