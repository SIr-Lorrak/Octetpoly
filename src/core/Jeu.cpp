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
	o = new Ordi [4-nbJoueur];
	nbTour = 1;
	joueurCourant = ordre[0];
}


void Jeu::ajouterJoueur()
{
	j[nbJoueur] = new Joueur;
	nbJoueur++;
	attendreNom = true;
}


void Jeu::ajouterLettre(const unsigned int n, const char lettre)
{
	j[n]->ajouterLettre(lettre);
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
				j[nbJoueur]->ajouterLettre(touche[0]);
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
#include "Jeu.h"

//-------------------------------------Constructeurs--------------------------------------

Jeu::~Jeu(){
	//TODO
}

//-------------------------------------Méthodes------------------------------------------
void Jeu::banque(){
	if(tourOrdi)
	{
		unsigned int posO = tabO[joueurCourant-1].getPos();
		if(true)
		{

		}

	}
	else
	{

	}

}

void Jeu::entreprise(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}

void Jeu::prison(){
	if(tourOrdi){
		

	}
	else{
		
	}
}

void Jeu::carteChance(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}

void Jeu::campagneDePub(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}

void Jeu::porteOuverte(){
	if(tourOrdi)
	{

	}
	else
	{
		
	}
}


//A mettre dans jeu 
void Jeu::actionCase(unsigned int num){
	//TODO enlever num pour le remplacer par tabJ[joueurCourant-1];
	Case & c = board.getCase(num);
	switch(c.getType()){
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

		case 'D':
			//TODO
			break;

		case 'P':
			prison();
			break;
	}
}

void Jeu::tourSuivant(){

}