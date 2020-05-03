#ifndef OCTET_ORDI_H
#define OCTET_ORDI_H

#include <iostream>

using namespace std;

#include "Pion.h"
#include "Plateau.h"
/**
@brief s'il n'y a pas quatre joueurs des ordis vont devoir remplacer les joueurs qui manquent
*/
class Ordi : public Pion{
	private : 
		int risque; //en pourcentage, ça correspond au risque que va prendre l'Ordi
	public :

		/**
		@brief constructeur par défaut de Ordi, il assigne un risque au hasard entre 0 et 100
		@param aucun
		*/
		Ordi();

		/**
		@brief constructeur de Ordi
		@param un entier r : représentant la constante de risque de l'Ordi
		*/
		Ordi(const unsigned int r);

		

		/**
		@brief renvoie true si l'Ordi décide d'acheter la banque, sinon false
		@param une Case banque : la banque en question
		*/
		bool AIacheteBanque(const Case * banque) const;


		/**
		@brief renvoie true si l'Ordi souhaite acheter l'entreprise, sinon false
		@param une Case entreprise : l'entreprise en question
		*/
		bool AIacheteEntreprise(const Case * entreprise) const;


		/**
		@brief renvoie un entier correspondant à l'investissement choisie (-1 dans l'illégal +1 dans le légal et 0 si rien n'est choisi)
		@param une Case entreprise : l'entreprise dans laquelle il va investir (ça doit être la case sur laquelle il se tient)
		*/
		int AIinvesti(const Case * entreprise) const;

		/**
		@brief renvoie l'indice de la case sur laquelle il veut organiser les championnats du monde (0 s'il ne veut rien faire)
		@param aucun
		*/
		unsigned int AIchampionat() const;

		/**
		@brief renvoie le nom de l'entreprise que l'Ordi souhaite vendre
		@param dejaVendu[], le tableau des noms d'entreprise déjà vendu ainsi que nbVente, sa longueur
		*/
		string AIvend(const string dejaVendu[],unsigned int nbVente)const;
};

#endif