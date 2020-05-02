#include "Jeu.h"
#include <iostream>

using namespace std;

//--------accesseurs--------//
void Jeu::getOrdre(unsigned int tab[4]) const
{
	for(int i =0; i<4 ; i++){ tab[i] = ordre[i];}
}

Case & Jeu::getJCase(const unsigned int i)
{
	return *board.getCase(i);
}

string Jeu::getChoix() const
{
	return choix;
}

unsigned int Jeu::getPrixAPayer(){
	return prixAPayer;
}

string Jeu::getVente(unsigned int indice)
{
	return vente[indice];
}

unsigned int Jeu::getNbVente() 
{
	return nbVente;
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
	else if(type=="attendreAmplete")
		return attendreAmplete;
	else if(type=="actionObligatoire")
		return actionObligatoire;
	else if(type=="vend")
		return vend;
	else if(type=="ad")
		return ad;
	else if(type=="porteO")
		return porteO;
	else if(type=="quitte")
		return quitte;
	else if(type=="pause")
		return pause;
	else if(type=="nouvellePartie")
		return nouvellePartie;
	else if(type=="desLancePrison")
		return desLancePrison;
	else if(type=="apresPorteOuverte")
		return apresPorteOuverte;
	else
		cout<<type<<endl;
		assert(false);
}

Joueur * Jeu::getJoueur(const unsigned int i) const
{
	assert(tabJ[i-1]!=NULL);
	assert(nbJoueur>=i);
	return tabJ[i-1];
}

Ordi * Jeu::getOrdi(const unsigned int i) const
{
	assert(tabO!=NULL);
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

Carte * Jeu::getCarte()const
{
	return chance;
}

unsigned int Jeu::getVainqueur() const
{
	return Vainqueur;
}

// permet de retourner l'évenement e
Evenement Jeu::gete(){

	return e;

}

//permet de retourner hacking h
Hacking Jeu::geth(){

	return h;

}

//retourne clicker c
Clicker Jeu::getc(){

	return c;

}

Escape Jeu::getes(){
	return es;
}

Lucky Jeu::getlu(){
	return lu;
}


//--------accesseurs--------//
//seteur permetant de mettre à jour l'évenement e
void Jeu::sete(unsigned int n){

	switch(n){

		case 1:
			e.Declenchement(getPion(joueurCourant)->getKarma());
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


//seteur permettant de mettre à jour clicker c
void Jeu::setc(){

	c.resetClicker();

}