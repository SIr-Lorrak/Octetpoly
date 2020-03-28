#ifndef OCTET_ORDI_H
#define OCTET_ORDI_H

#include <iostream>

using namespace std;

#include "Pion.h"
#include "Plateau.h"

class Ordi : public Pion{
	private : 
		unsigned int risque; //en pourcentage, ça correspond au risque que vas prendre l'Ordi
	public :

		/**
		@brief constructeur par défaut de Ordi il assigne un risque au hasard entre 0 et 100
		@param aucun
		*/
		Ordi();

		/**
		@brief constructeur de Ordi
		@param un entier r : représentant la constante de risque de l'Ordi
		*/
		Ordi(const unsigned int r);

		

		/**
		@brief renvoie true si l'Ordi décide d'acheté la banque false sinon
		@param une Case banque : la banque en question
		*/
		bool AIacheteBanque(const Case & banque) const;


		/**
		@brief renvoie true si l'Ordi souhaite acheté l'entreprise false sinon
		@param une Case entreprise : l'entreprise en question
		*/
		bool AIacheteEntreprise(const Case & entreprise) const;


		/**
		@brief renvoie in entier correspondant a l'investissement choisit (-1 dans l'illégal +1 dans le légal et 0 si rien n'est choisi)
		@param une Case entreprise : l'entreprise dans laquel il vas investir (ça doit être la case sur laquel il se tient)
		*/
		int AIinvesti(const Case & entreprise) const;

		/**
		@brief renvoie l'indice de la case sur laquel il veut organisé les championa du monde (0 si il ne veut rien faire)
		@param aucun
		*/
		unsigned int AIchampionat() const;


		unsigned int AIporteOuverte(const Plateau & board)const;
};

#endif