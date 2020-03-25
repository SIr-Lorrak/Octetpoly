#include <iostream>
#include <string>
using namespace std;

#include "Evenement.h"


/**
brief permet le fonctionnement du jeu peut importe le type d'affichage
*/
class Jeu {

private:

	Evenement e;
	Hacking h;
	clicker c;

	
public:

	/**
	brief seteur permetant de mettre à jour l'évenement e
	param unsigned int n(valeurs qui differents selon ce que l'on veut mettre à jour) 
	*/
	void sete(unsigned int n);

	/**
	brief seteur permetant de mettre à jour hacking h
	param unsigned int n(valeurs qui differents selon ce que l'on veut mettre à jour) 
	*/
	void seth(unsigned int n);

	/**
	brief permet de retourner l'évenement e
	param none
	*/
	Evenement gete();

	/**
	brief permet de retourner hacking h
	param none
	*/
	Hacking geth();

	/**
	brief permet d'effectuer une action selon la touche appuyer
	param none
	*/
	void actionClavier(const string touche);

	/**
	brief retourne clicker c
	param none
	*/
	clicker getc();


};
