#include <assert.h>
#include <time.h>
#include <unistd.h>

#include "Jeu.h"

using namespace std;

const string KONAMI_CODE[10] = {"^","^","v","v","<",">","<",">","b","a"};//suite de 10 touches pour activer le konami code

//-------------------------------------Constructeurs--------------------------------------

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
	casePub = 0;
	coeffAd = 1.0;

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


//-------------------------------------Méthodes--------------------------------
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
	if(n!=0){
		for(unsigned int i=0;i<n;i++){
			if(o[i].getNom()==nom){
				return true;
			}
		}
	}
	return false;
}


void Jeu::commencerPartie()
{	
	
	if(nbJoueur<4){
		delete [] tabO;
		tabO = new Ordi [4-nbJoueur];
	
		do{
			for(unsigned int i = 1;i<4-nbJoueur;i++){
				do{
					tabO[i].nomAleatoire();
				}while(nomExiste(tabO[i].getNom(),tabO,i));
			}
		}while(!nomExiste("[bot] M. Pronost le meilleur prof de la terre",tabO,4-nbJoueur));
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
	else if(attendreAmplete){
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

void Jeu::investirEJoueur(const string touche){
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());
	Pion * p = getPion(joueurCourant);

	//Est-ce que le joueurCourant veux investir
	//Est-ce que le joueurCourant a assez d'argent
	if(touche == "+" && p->getCoin() >= c->getPrixB())
	{
		p->investit(1,c);
	}

	//Est-ce que le joueurCourant a assez d'argent
	else if (touche == "-" && p->getCoin() >= c->getPrixM())
	{
		p->investit(-1,c);
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
		if(occupant == 0)//Différent cas de figure
		{
			//N'appartient à personne,le JOUEUR peut acheter la banque
			//Est-ce que le JOUEUR veut acheter
			//Et est-ce qu'il a assez d'argent pour
			if((touche == "o" ||touche == "O" || touche == "enter") && coinCourant >= c->getPrixInitial())
			{
				getPion(joueurCourant)->achete(c);
						
				//Investissement uniquement possible pour une entreprise
				if(c->getType() == 'E')
				{
					investirEJoueur(touche);
					coinCourant = getPion(joueurCourant)->getCoin();
				}
			}
		}

		else{
				payeLoyerJoueur();
				//On met à jour la variable coinCourant 
				coinCourant = getPion(joueurCourant)->getCoin();
		}
	}
//La case appartient au JOUEUR	
//Si c'est une entreprise, il pourra peut-être investir
	else if (c->getType() == 'E')
	{
		investirEJoueur(touche);
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


void Jeu::payeLoyerJoueur(){
//C'est un joueur qui joue	
	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	unsigned int coinCourant = getPion(joueurCourant)->getCoin();

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
			//getPion(joueurCourant)->vend(); on passe dans l'interface de vente
		}
	}
	else
	{
		//faillite
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

void Jeu::campagneDePub(const string touche){
	Case * c = board.getCase(16);//ATTENTION APPEL FRAUDULEUX
	unsigned int coinCourant = getPion(joueurCourant)->getCoin();
	if(coinCourant >= c->getPrix())
	{
		unsigned int Case = 1;//TODO
		pub(Case);
		getPion(joueurCourant)->setCoin(coinCourant - c->getPrix());	
	}
	
}

void Jeu::actionCase(const string & touche){

	//La case où se trouve le joueurCourant
	Case * c = board.getCase(getPion(joueurCourant)->getPos());

	switch(c->getType()){
		case 'E':
			actionBE(touche);
			break;

		case 'B':
			actionBE(touche);
			break;

		case 'C':
			//carteChance();
			break;

		case 'A':
			campagneDePub(touche);
			break;

		case 'O':
			//porteOuverte();
			break;

		case 'I':
			//TODO 
			break;

		case 'P':
			//prison();
			break;
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
#include <iostream>
#include <string>
using namespace std;

#include "Jeu.h"


//seteur permetant de mettre à jour l'évenement e
void Jeu::sete(unsigned int n){

	switch(n){

		case 1:
			e.Declenchement();
			break;

		case 2:
			e.fini(getc().getnbclique());
			break;

	}
}


//seteur permetant de mettre à jour hacking h
void Jeu::seth(unsigned int n){

	switch(n){

		case 1:
			h.intAff = 0;
			break;

		case 2:
			h.intAff = 1;
			break;

		case 3:
		h.resetHack();
		break;
	}
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
void Jeu::actionClavier(const string touche){

	//si nous sommes dans l'évenement hacking
	if (e.getn() == "hack"){

		if (touche == "\n"){
			h.valider();
		}
		else{
			h.saisir(touche);
		}
	}

	//si nous sommes dans l'évenement clicker
	if(e.getn() == "clicker"){
		if(touche == " "){
			c.ajoutClique(gete().gettempsD());
		}
	}
}


//retourne clicker c
clicker Jeu::getc(){

	return c;

}


//seteur permettant de mettre à jour clicker c
void Jeu::setc(){

	c.resetClicker();

}