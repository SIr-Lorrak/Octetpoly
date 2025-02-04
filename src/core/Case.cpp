#include "Case.h"
#include <iostream>

using namespace std;

//---------------------------------Constructeurs------------------------------------------
//Crée une case (constructeur par défaut)
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	groupe = 0;
	karmaCase = 0;

	ad = false;
	coeffAd = 1.0;
	nom="";

	prix = 0;
	prixInitial = 0;

	loyer = 0;
	loyerInitial = 0;

	prixM = 0;
	prixMInitial = 0;

	prixB = 0;
	prixBInitial = 0;

	prixDeVente = 0;
	prixDeVenteInitial = 0;

	coeffUn = 0;
	coeffDeux = 0;
	coeffTrois = 0;
	coeffQuatre = 0;
	coeffCinq = 0;
}


//Destructeur de la classe
Case::~Case(){
	//TODO
}


//Set les différents attributs Variable de Case
void Case::set(unsigned int p,unsigned int l,unsigned int prixdevente,unsigned int pM,unsigned int pB,unsigned int prop, int i){
	prix = p;
	loyer = l;
	prixDeVente = prixdevente;
	prixM = pM;
	prixB = pB;
	occupation = prop;
	investissement = i;
}

//-------------------------------------Getters-------------------------------------------

//Renvoie le Nom de la Case
string Case::getNom() const{
	return nom;
}


//Indique à qui appartient l'entreprise ou la banque
unsigned int Case::getOccupation() const{
	return occupation;
}


//Indique le prix de l'entreprise ou de la banque
unsigned int Case::getPrix() const{
	return prix;
}


//Indique le prix d'un investissement illégal (mauvais)
unsigned int Case::getPrixM() const{
	return prixM;
}


//Indique le prix d'un investissement légal (bon)
unsigned int Case::getPrixB() const{
	return prixB;
}


//Renvoie le Loyer d'une Case (ce que les joueurs doivent payer en tombant dussus)
unsigned int Case::getLoyer() const{
	return loyer;
}


//Informe sur le prix initial de l'entreprise ou banque
unsigned int Case::getPrixInitial() const{
	return prixInitial;
}


//Informe sur le prix de vente de l'entreprise ou de la banque
unsigned int Case::getPrixDeVente() const{
	return prixDeVente;
}


//Indique l'investissement de l'entreprise
int Case::getInvestissement() const{
	return investissement;
}


//Récupére le type de la case
char Case::getType() const{
	return type;
}


//Indique si la Case est en campagne de Pub ou pas
bool Case::getAd() const{
	return ad;
}


//Renvoie le numero du groupe de la Case
unsigned int Case::getGroup() const{
	return groupe;
}


//Renvoie le Karma d'une Case (taux d'impact sur le karma des Pions)
unsigned int Case::getKarmaCase() const{
	return karmaCase;
}

//-------------------------------------Setters-------------------------------------------

//Set le propriétaire d'une Case (/!\ uniquement lors du chargement d'une sauvegarde normalement)
void Case::setOccupation(unsigned int r){
	occupation = r;
}

//-------------------------------------Méthodes------------------------------------------

// Permet l'initialisation d'une case au lancement d'une partie 
//Dans l'ordre suivant
//(groupe ; type; prix ; nom ; karmaCase ; prixDeVente ; prixMauvais ; 
//prixBon ; loyer ; coeffUn ; coeffDeux ; coeffTrois ; coeffQuatre ; coeffCinq)
void Case::initCase(unsigned int group,char categorie,unsigned int p,
					string n,unsigned karma,unsigned int pV,
					unsigned int pM,unsigned int pB,unsigned int l,
					float c1,float c2,float c3,float c4,float c5){
	nom = n;
	type = categorie;
	groupe = group;
	karmaCase = karma;

	prixInitial = p;
	prix = prixInitial;
	
	prixDeVenteInitial = pV;
	prixDeVente = prixDeVenteInitial;

	prixMInitial = pM;
	prixM = prixMInitial;

	prixBInitial = pB;
	prixB = prixBInitial;

	loyerInitial = l;
	loyer = loyerInitial;

	coeffUn = c1;
	coeffDeux = c2;
	coeffTrois = c3;
	coeffQuatre = c4;
	coeffCinq = c5;

}


//Initialise les prix initiaux d'une entreprise ou d'une banque
void Case::initPrixInitial(){
	//Utile pour la fonction investissement car quand on investit, c'est qu'on posséde
	//la case ainsi le loyer initial est égal au prixInitial*2 après achat
	if(occupation > 0)
	{
		prix = 2*prixInitial;
	}

	//Utile pour la fonction reset, on remet bien tout au prix initial vu que la 
	//case n'appartient plus à personne
	else
	{
		prix = prixInitial;
	}

	prixDeVente = prixDeVenteInitial;
	prixM = prixMInitial;
	prixB = prixBInitial;
	loyer = loyerInitial; 
}


//Change l'investissment, le prix,le loyer,le prix de vente,le prixB, le prixM
void Case::investir(int i){
	assert(i != 0);

	//Vérifie si l'entreprise n'a pas changé de politique (Passer de l'illégale ou légale)
	//ou inversement
	if((investissement > 0 && i == -1) || (investissement < 0 && i == 1))
	{
		initPrixInitial();
		investissement = 0;
	}


	if(i == -1)
	{
		investissement--;
		prixM = prixM*1.2;
	}

	else 
	{
		investissement++;
		prixB = prixB*1.3;
	}

	//Investissement > 0 : on opte pour une politique légal
	//Investissement < 0 : on opte pour une politique illégal
	switch(investissement){
		case 1:
			loyer = loyer*coeffUn;
			prix = prix*4.5;
			prixDeVente = prixDeVente*4.5;
			break;

		case 2:
			loyer = loyer*coeffDeux;
			prix = prix*3;
			prixDeVente = prixDeVente*3;
			break;

		case 3:
			loyer = loyer*coeffTrois;
			prix = prix*3;
			prixDeVente = prixDeVente*3;
			break;

		case 4:
			loyer = loyer*coeffQuatre;
			prix = prix*2;
			prixDeVente = prixDeVente*2;
			break;

		case 5:
			loyer = loyer*coeffCinq;
			prix = prix*1.5;
			prixDeVente = prixDeVente*1.5;
			break;

		case -1:
			loyer = loyer*(coeffUn+0.1);
			prix = prix*1.2;
			prixDeVente = prixDeVente*1.2;
			break;

		case -2:
			loyer = loyer*(coeffDeux+0.1);
			prix = prix*1.4;
			prixDeVente = prixDeVente*1.4;
			break;

		case -3:
			loyer = loyer*(coeffTrois+0.1);
			prix = prix*1.6;
			prixDeVente = prixDeVente*1.6;
			break;

		case -4:
			loyer = loyer*(coeffQuatre+0.1);
			prix = prix*1.8;
			prixDeVente = prixDeVente*1.8;
			break;

		case -5:
			loyer = loyer*(coeffCinq+0.1);
			prix = prix*2;
			prixDeVente = prixDeVente*2;
			break;
	}
}


//Affecte un propriètaire et change les prix
void Case::estAcheter(unsigned int i){
	occupation = i;
	prix = prix*2;
}


//Indique que l'entreprise fait de la pub (Change les prix)
void Case::advertising(){
	ad = true;
	coeffAd = coeffAd*1.2;
	prix = prix*coeffAd;
	loyer = loyer*coeffAd;
	prixDeVente = prixDeVente*coeffAd;
}


//Indique que l'entreprise ne fait plus de pub (Change les prix)
void Case::endAdvertising(){
	ad = false;
	prix = prix/coeffAd;
	loyer = loyer/coeffAd;
	prixDeVente = prixDeVente/coeffAd;
	coeffAd = 1.0;
}


//Réinitialisation de la case
void Case::reset(){
	occupation = 0;
	investissement = 0;
	ad = false;
	coeffAd = 1.0;

	//On réinitialise les prix
	initPrixInitial();
}

//-------------------------------------TEST REGRESSION-----------------------------------

void Case::affichageRegression(){
	cout << endl << "Affichage : ........" << endl;
	cout << "ad : " << ad << endl; 
	cout << "coeffAd : " << coeffAd << endl; 
	cout << "nom : " << nom << endl;
	cout << "occupation : " << occupation << endl;
	cout << "type : " << type << endl; ; 
	cout << "investissement : " << investissement << endl; 
	cout << "groupe : " << groupe << endl;
	cout << "karma : " << karmaCase << endl;

	cout << "loyer : " << loyer << endl; 
	cout << "loyerInitial : " << loyerInitial << endl;

	cout << "prix :" << prix << endl; 
	cout << "prixInitial : " << prixInitial << endl;

	cout << "prixM : " << prixM << endl; 
	cout << "prixMInitial : " << prixMInitial << endl;

	cout << "prixB : " << prixB << endl; 
	cout << "prixBInitial : " << prixBInitial << endl;

	cout << "prixDeVente : " << prixDeVente << endl ;
	cout << "prixDeVenteInitial : " << prixDeVenteInitial << endl;
}

void Case::testRegressionCase(){
	cout << endl << endl;
	cout << "Appel initCase() : ....." << endl;
	//initCase(1,'E',35,"testEntreprise",10,45,7,42,69);
	affichageRegression();

	cout << endl << "Appel estAcheter() : ....." << endl;
	estAcheter(2);
	affichageRegression();

	cout << endl << "Investissement +2" << endl; 
	investir(1);
	investir(1);
	affichageRegression();
	
	cout << endl << "Investissement -2" << endl;
	investir(-1);
	investir(-1);
	affichageRegression();
	
	cout << endl << " Appel advertising() :....." << endl;
	advertising();
	affichageRegression();

	cout << endl << " Appel endAdvertising() :....." << endl;
	endAdvertising();
	affichageRegression();

	cout << endl << " Appel initPrixInitial() :....." << endl;
	initPrixInitial();
	affichageRegression();

	cout << endl << "Appel Reset() :....." << endl;
	reset();
	affichageRegression();
}