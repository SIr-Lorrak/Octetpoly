#include <assert.h>
#include <time.h>
#include <unistd.h>

#include "Jeu.h"

using namespace std;

const string KONAMI_CODE[10] = {"^","^","v","v","<",">","<",">","b","a"};//suite de 10 touches pour activer le konami code

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



	konamiCode("");

	attendreNom = false;
	desLance = false;
	avance = false;
	confirmation = false;
	attendreAmplete = true;
	tourFini = false;

	tourOrdi = false;

	nbJoueur = 0;
	nbTour = 0;

	tabO = new Ordi[0];
	unsigned int alea;
	alea = 0;
	for(unsigned int i=0;i<4;i++){
		do{
			alea = rand()%4+1;
		}while(!estPasDans(alea,ordre,i));
		ordre[i] = alea;
	}
}


void Jeu::getOrdre(unsigned int tab[4]) const
{
	for(int i =0; i<4 ; i++){ tab[i] = ordre[i];}
}

Case & Jeu::getJCase(const unsigned int i)
{
	return *board.getCase(i);
}

bool Jeu::getBool(const string & type) const
{
	if(type=="attendreNom")
		return attendreNom;
	else if(type=="avance")
		return avance;
	else if(type=="confirmation")
		return confirmation;
	else if(type=="desLance")
		return desLance;
	else if(type=="tourOrdi")
		return tourOrdi;
	else
		assert(false);
}

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

unsigned int Jeu::getNbJoueur()const
{
	return nbJoueur;
}


unsigned int Jeu::getNbTour() const
{
	return nbTour;
}

unsigned int Jeu::getJoueurCourant()const
{
	return joueurCourant;
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

bool nomExiste(const string & nom,const Ordi o[],unsigned int n){
	for(unsigned int i=0;i<n;i++){
		if(o[i].getNom()==nom){
			return true;
		}
	}
	return false;
}


void Jeu::commencerPartie()
{
	if(nbJoueur<4){
		delete [] tabO;
		tabO = new Ordi [4-nbJoueur];
	}
	for(unsigned int i = 1;i<4-nbJoueur;i++){
		do{
			tabO[i].nomAleatoire();
		}while(nomExiste(tabO[i].getNom(),tabO,i));
	}
	tourSuivant();
}


void Jeu::ajouterJoueur()
{
	tabJ[nbJoueur] = new Joueur;
	nbJoueur++;
	attendreNom = true;
}


void Jeu::enleverJoueur()
{
	nbJoueur--;
	delete tabJ[nbJoueur];
}


void Jeu::ajouterLettre(const unsigned int n, const string lettre)
{
	assert(n<nbJoueur);
	tabJ[n]->ajouterLettre(lettre);
}


void Jeu::resetBool()
{
	konamiCode("");

	desLance = false;
	avance = false;
	confirmation = false;
	attendreAmplete = true;
	tourFini = false;
}

void Jeu::tourSuivant(){
	nbTour++;
	unsigned int i=0;
	while(joueurCourant!=ordre[i]){
		i++;
	}

	joueurCourant = ordre[(i+1)%4];

	resetBool();
	if(joueurCourant>nbJoueur) tourOrdi = true ;
	else tourOrdi = false ;
}


void Jeu::actionPartie(const string & touche)
{
	Pion *p = getPion(joueurCourant);
	/*if(p->getPrisonnier()){

	}*/
	if(!desLance){
		if(touche == "\n"){
			p->lanceDes();
			desLance = true;
		}
	}
	else if(!avance){
		if(touche == "\n"){
			p->avancer();
			avance = true;
			attendreAmplete = false;// a enlever plus tard
		}
	}
	if(attendreAmplete){
		actionCase(touche);
	}
	else if(!tourFini){
		if(tourOrdi){
			tourFini = true;
		}
		else{
			if(touche=="\n"){
				tourFini = true;
				e.Declenchement();
			}
		}
	}
	else{
		tourSuivant();
	}
}


void Jeu::actionMenu(const string & touche)
{
	if(!attendreNom&&nbJoueur<4){
		if(!confirmation){
			if(touche == "+"){
				ajouterJoueur();//1 ajoute un joueur quand on appuie sur plus et attend son nom
			}

			if(touche == "-"&&nbJoueur>0){
				enleverJoueur();
			}
		}

		if(touche == "\n"||((touche=="o"||touche=="O")&&confirmation)){
			if(confirmation){
				commencerPartie();
				confirmation=false;
			}

			confirmation = true;
		}

		if(touche=="n"||touche=="N"){
			confirmation=false;
		}
	}

	else if(attendreNom){
		if(touche == "\n"){// \n c'est pour 'entrer' ou 'retour'
			attendreNom = false;//2 entrer valide le nom du joueur
		}

		else if(touche[0]==127||touche[0]==8||touche[0]=='\b'){// = pour 'effacer'
			tabJ[nbJoueur-1]->effacerLettre();
		}

		else{
			ajouterLettre(nbJoueur-1,touche);//ajoute la lettre rentrer dans le nom du joueur
		}
	}

	if(nbJoueur==4&&!attendreNom){
		if((touche=="o"||touche=="O"||touche=="\n")&&confirmation){
			confirmation = false;
			commencerPartie();
		}

		if(!confirmation) confirmation = true;

		else if(touche=="n"||touche=="N"||touche=="-"){
			confirmation = false;
			enleverJoueur();
		}

	}
}


void Jeu::actionClavier(const string & touche)
{
	if(nbTour == 0){
		actionMenu(touche);
	}

	else if(e.getn()=="rien"){
		konamiCode(touche);//pour le konami code
		actionPartie(touche);
	}
	else{
		actionMiniJeu(touche);
	}
}

void Jeu::actionOrdi(){
	actionClavier("\n");
	//Ordi o = *getOrdi(joueurCourant);
	/*if(avance){
		if(o.AIacheteEntreprise(*board.getCase(o.getPos()))){
			actionCase("o");
		}
	}*/
}




//A mettre dans jeu 
void Jeu::actionCase(const string & touche){
	
}



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
	assert(n==1||n==2);
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
		else if(touche[0]==127||touche[0]==8||touche[0]=='\b'){
			h.effacerLettre();
		}
		else{
			h.saisir(touche);
		}
	}

}

Jeu::~Jeu(){
	delete [] tabO;
	for(unsigned int i=0; i<nbJoueur; i++){
		delete tabJ[i];
	}
}