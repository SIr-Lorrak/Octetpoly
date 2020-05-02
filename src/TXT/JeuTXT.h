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

	/**
	@brief permet l'affichage du menu de pause
	@param none
	*/
	void affichagePause() const;

	/**
	@brief permet l'affichage de la campagne de pub
	@param none
	*/
	void affichageCampagneDePub();

	/**
	@brief permet l'affichage de la porte ouverte
	@param none
	*/
	void affichagePorteOuvete();

	/**
	@brief permet l'affichage du mode vente si on à plus de sous
	@param none
	*/
	void affichageVente();

	/**
	@brief permet l'affichage d'une case
	@param none
	*/
	void affichageCase(const Case * c);

	/**
	@brief permet l'affichage txt du jeu
	@param none
	*/
	void affichageJeu();

	/**
	@brief permet l'affichage su mini jeu clicker
	@param none
	*/
	void affichageClicker();

	/**
	@brief permet l'affichage du mini jeu escape
	@param none
	*/
	void affichageEscape();

	/**
	@brief permet l'affichage du mini jeu Lucky
	@param none
	*/
	void affichageLucky();

	/**
	@brief permet l'affichage txt de l'évenement hacking
	@param none
	*/
	void affichageHacking();

	/**
	@brief permet l'affichage de la victoire
	@param none
	*/
	void affichageVictoire();

	/**
	@brief permet de mettre a jour les objets suite à l'appuie d'une touche
	@param none
	*/
	void update();

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
