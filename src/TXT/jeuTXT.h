#include <iostream>
#include <string>
using namespace std;


#include "../core/Evenement.h"
#include "../core/Jeu.h"



/**
brief classe qui gère le jeu en affichage TXT
*/
class jeuTXT{

private:

		Jeu j;

public:

	/**
	brief constructeur, vide le terminal
	param none
	*/
	jeuTXT();

	/**
	brief permet le deroulement de la partie
	param none
	*/
	void deroulementTXT();

	/**
	brief permet l'affichage txt de l'évenement hacking
	param none
	*/
	void affichageHacking();

	/**
	brief permet de mettre a jour les objets suite à l'appuie d'une touche
	param none
	*/
	void update();

};