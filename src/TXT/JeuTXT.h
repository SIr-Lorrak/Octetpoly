#ifndef OCTET_JEUTXT_H
#define OCTET_JEUTXT_H

#include <iostream>
#include <string>
using namespace std;


#include "../core/Evenement.h"
#include "../core/Jeu.h"



/**
@brief classe qui gère le jeu en affichage TXT
*/
class JeuTXT{

private:

		Jeu j;
		bool action;


	/**
	@brief permet l'affichage txt du menu de départ
	@param none
	*/
	void affichageMenu();

	void affichageCampagneDePub();

	void affichageCase(const Case & c);

	/**
	@brief permet l'affichage txt du jeu
	@param none
	*/
	void affichageJeu();


	void affichageClicker();

	/**
	@brief permet l'affichage txt de l'évenement hacking
	@param none
	*/
	void affichageHacking();

	/**
	@brief permet de mettre a jour les objets suite à l'appuie d'une touche
	@param none
	*/
	bool update();

	/**
	@brief affiche le jeu dans un terminal
	@param none
	*/
	void affichage();

public:

	/**
	@brief constructeur, vide le terminal
	@param none
	*/
	JeuTXT();

	/**
	@brief permet le deroulement de la partie
	@param none
	*/
	void run();


};

#endif
