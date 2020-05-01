#include "Jeu.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



bool estPasDans(const unsigned int n, const unsigned int tab[],const unsigned int taille){
	if(taille == 0) return true;
	for(unsigned int i=0;i<taille;i++){
		if(tab[i]==n) return false;
	}
	return true;
}

//transforme une chaine de caractère avec des espaces en remplacent les expaces par des underscores _
string SpaceToUnderscore(const string & nom){
	string nomr = nom;
	unsigned int i= 0;
	while(nom.c_str()[i] != '\0'){
		if(nom[i]==' '){
			nomr[i]='_';
		}
		i++;
	}
	return nomr;
}

//transforme une chaine de caractère sans espace en remplacent les underscores _ par des espaces
string UnderscoreToSpace(const string & nom){
	string nomr = nom;
	unsigned int i= 0;
	while(nom[i] != '\0'){
		if(nom[i]=='_'){
			nomr[i]=' ';
		}
		i++;
	}
	return nomr;
}

void Jeu::sauver(const string & file) const 
{
	ofstream fichier(file.c_str());
	assert(fichier.is_open());
	//TODO
	fichier<<"OCTETPOLY666"<<endl<<nbJoueur<<endl;
	for(unsigned int i = 0;i<4;i++){
		fichier<<ordre[i]<<" ";
	}
	fichier<<endl<<joueurCourant<<endl;
	for(unsigned int i = 1;i<=4;i++){
		if(getPion(i)->getNom().length()>0){
			fichier<<SpaceToUnderscore(getPion(i)->getNom())<<" ";//nom des Joueurs
		}
		else{
			fichier<<"<anonyme> ";
		}
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getPos()<<" ";//position des Joueurs
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getCoin()<<" ";//argents des Joueurs
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<getPion(i)->getKarma()<<" ";
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		if(getPion(i)->getPrisonnier()){
			fichier<<"1 ";
		}
		else{
			fichier<<"0 ";
		}
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		if(getPion(i)->getTicket()){
			fichier<<"1 ";
		}
		else{
			fichier<<"0 ";
		}
	}
	fichier<<endl;
	for(unsigned int i = 1;i<=4;i++){
		fichier<<char(int('a')+int(getPion(i)->getCar()))<<" ";
	}
	fichier<<endl;
	fichier<<board.getcasePub()<<endl;
	for(unsigned int i = 0;i<32;i++){
		const Case * c = board.getCase(i);
		fichier<<c->getPrix()<<" "<<c->getLoyer()<<" "
		<<c->getPrixDeVente()<<" "<<c->getPrixM()<<" "
		<<c->getPrixB()<<" "<<c->getOccupation()<<" "
		<<c->getInvestissement()<<endl;
	}
	for(unsigned int i = 1;i<=4;i++){
		Pion * p = getPion(i);
		fichier<<p->getNbPropriete()<<endl;
		for(unsigned int j=0;j<p->getNbPropriete();j++){
			fichier<<board.getIndice(p->getPropriete(j)->getNom())<<" ";
		}
		fichier<<endl;
	}
	fichier.close();
}


bool Jeu::charger(const string & file)
{
	bool valide = true;
	ifstream fichier(file.c_str());
	assert(fichier.is_open());
	string recup;
	int recupint;
	fichier>>recup;
	if(recup == "OCTETPOLY666"){
		fichier>>nbJoueur;
		for(unsigned int i=0;i<nbJoueur;i++){
			tabJ[i]=new Joueur;
			tabJ[i]->setRang(i+1);
		}
		tabO = new Ordi [4-nbJoueur];
		for(unsigned int i=0;i<4-nbJoueur;i++){
			tabO[i].setRang(nbJoueur+i+1);
		}

		for(unsigned int i= 0; i<4;i++){
			fichier>>ordre[i];
		}
		fichier>>joueurCourant;
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recup;
			getPion(i)->setNom(UnderscoreToSpace(recup));
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			getPion(i)->setPos(recupint);
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			getPion(i)->setCoin(recupint);
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			getPion(i)->setKarma(recupint);
		}
		for(unsigned int i = 1;i<=4;i++){
			fichier>>recupint;
			if(recupint==1){
				getPion(i)->setPrisonnier();
			}
		}
		for(unsigned int i=1;i<=4;i++){
			fichier>>recupint;
			if(recupint == 1){
				getPion(i)->donTicket();
			}
		}
		for(unsigned int i=1;i<=4;i++){
			fichier>>recup;
			getPion(i)->setCar(char(int(recup[0])-int('a')));
		}
		fichier>>recupint;
		if(recupint!=0){
			board.setcasePub(recupint);
		}
		for(unsigned int i = 0;i<32;i++){
			unsigned int prix,loyer,prixdevente,prixM,prixB,proprio;
			int investissement;
			fichier>>prix>>loyer>>prixdevente>>prixM>>prixB>>proprio>>investissement;
			board.setCase(i,prix,loyer,prixdevente,prixM,prixB,proprio,investissement);
		}

		for(unsigned int i=1;i<=4;i++){
			unsigned int nbProp;
			fichier>>nbProp;
			for(unsigned int j=0;j<nbProp;j++){
				fichier>>recupint;
				getPion(i)->don(board.getCase(recupint));
			}
		}
	}
	else{
		valide = false;
	}

	fichier.close();
	tourSuivant();
	return valide;
}

bool fichierExiste(const string & file)
{
	bool retour;
	ifstream fichier(file.c_str());
	retour = fichier.is_open();
	if(retour){
		string format;
		fichier>>format;
		if(format != "OCTETPOLY666"){
			retour = false;
		}
	}
	fichier.close();
	return retour;
}