#include <time.h>
#include <unistd.h>

#include "Jeu.h"

using namespace std;

const string KONAMI_CODE[10] = {"^","^","v","v","<",">","<",">","b","a"};//suite de 10 touches pour activer le konami code

//-------------------------------------Constructeurs---------------------------
Jeu::Jeu(){
	srand(time(NULL));



	konamiCode("");

	attendreNom = false;
	desLance = false;
	avance = false;
	confirmation = false;
	attendreAmplete = true;
	actionObligatoire = true;
	vend = false;
	ad = false;
	porteO = false;
	quitte = false;
	pause = false;
	Vainqueur=0;
	nouvellePartie = false;
	desLancePrison = false;
	choix = "";
	nbVente = 0;
	for (int i = 0; i < 24; ++i)
	{
		vente[i] = "";
	}
	prixAPayer = 0;
	chance = NULL;

	tourOrdi = false;

	nbJoueur = 0;
	nbTour = 0;

	tabO = NULL;
	unsigned int alea;
	alea = 0;
	for(unsigned int i=0;i<4;i++){
		do{
			alea = rand()%4+1;
		}while(!estPasDans(alea,ordre,i));
		ordre[i] = alea;
	}
	joueurCourant = ordre[0];
}


//-----------------------Méthodes-----------------------


void Jeu::testRegression(){
	Jeu j;
	j.commencerPartie();
	j.sauver("data/sauvegarde/test.save");
	Jeu y;
	y.charger("data/sauvegarde/test.save");
	y.tourSuivant();
	y.tourSuivant();
	y.sauver("data/sauvegarde/toast.save");
}

Jeu::~Jeu(){
	if(tabO!=NULL){
		delete [] tabO;
	}
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}

//les autres fonctions sont contenuent dans 