#include <assert.h>
#include <time.h>

#include "Jeu.h"

using namespace std;

const string KONAMI_CODE[10] = {"^","^","v","v","<",">","<",">","b","a"};

bool estPasDans(const unsigned int n, const unsigned int tab[],const unsigned int taille = 4){
	if(taille == 0) return true;
	for(unsigned int i=0;i<taille;i++){
		if(tab[i]==n) return false;
	}
	return true;
}

//-------------------------------------Constructeurs--------------------------------------

Jeu::Jeu(){
	srand(time(NULL));
	attendreNom = false;
	desLance = false;
	avance = false;
	tourOrdi = false;
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
	nbTour++;
	joueurCourant = ordre[nbTour%5 - 1];
	if(joueurCourant>nbJoueur) tourOrdi = true ;
	else tourOrdi = false ;
}

void Jeu::actionPartie(const string & touche)
{
	if(tourOrdi){

	}
	else{
		if(!desLance){
			if(touche == "\n"){
				tabJ[joueurCourant]->lanceDes();
				desLance = true;
			}
		}
		else if(!avance){
			if(touche == "\n"){
				tabJ[joueurCourant]->avancer();
			}
		}
	}
}


void Jeu::actionClavier(const string & touche)
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
		actionPartie(touche);
	}
	if(touche != "\n"){
		confirmation = false;
	}
}

Jeu::~Jeu(){
	delete [] tabO;
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}

void Jeu::banque(){
	
}

void Jeu::entreprise(){
	
}

void Jeu::prison(){
	
}

void Jeu::carteChance(){
	
}

void Jeu::campagneDePub(){
	
}

void Jeu::porteOuverte(){
	
}


//A mettre dans jeu 
void Jeu::actionCase(unsigned int num){
	//TODO enlever num pour le remplacer par tabJ[joueurCourant-1];
	Case c = *board.getCase(num);
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
		default :
			bool Case_Invalide = false;
			assert(Case_Invalide);
			break;
	}
}

using namespace std;



//seteur permetant de mettre à jour l'évenement e
void Jeu::sete(unsigned int n){

	switch(n){

		case 1:
			e.Declenchement();
			break;

		case 2:
			e.fini();
			break;

	}
}


//seteur permetant de mettre à jour hacking h
void Jeu::seth(unsigned int n){
	h.intAff = n-1;
}


// permet de retourner l'évenement e
Evenement Jeu::gete(){

	return e;

}


//permet de retourner hacking h
Hacking Jeu::geth(){

	return h;

}


//permet d'effectuer une action selon la touche appuyer
void Jeu::actionMiniJeu(const string touche){

	//si nous sommes dans l'évenement hacking
	if (e.getn() =="hack"){

		if (touche == "\n"){
			h.valider();
		}
		else if(touche== "="){
			h.effacerLettre();
		}
		else{
			h.saisir(touche);
		}
	}

}
