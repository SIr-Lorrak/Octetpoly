#ifndef OCTET_ORDI_H
#define OCTET_ORDI_H

#include <iostream>

using namespace std;


#include "Plateau.h"
#include "Pion.h"

class Ordi : public Pion{
	private : 
		
	public :
		/**
		@brief
		@param
		*/
		bool AIacheteBanque(const float prix);

		/**
		@brief
		@param
		*/
		bool AIacheteEntreprise(const float prix);


		/**
		@brief
		@param
		*/
		int AIinvesti(const float prixB,const float prixM) const;

		/**
		@brief
		@param
		*/
		unsigned int AIchampionat(Plateau p) const;
};

#endif