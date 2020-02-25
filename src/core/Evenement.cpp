#include "Evenement.h"

Evenement::Evenement()
{
	nom = "none";
	type = false;
	chance = 0;
}

Evenement::Evenement(const sting n,const unsigned int ch,const bool t)
{
	nom = n;
	chance = ch;
	type = t;
}

Evenement::setNom